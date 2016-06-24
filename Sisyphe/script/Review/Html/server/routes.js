(function() {
 
  'use strict';
  var express = require('express');
  var router = express.Router();
  var fs = require('fs');
  var path = require('path');
  var spawn = require('child_process').spawn;
  
  var iconvlite = require('iconv-lite');
  function readFileSync_encoding(filename, encoding) {
      var content = fs.readFileSync(filename);
      return iconvlite.decode(content, encoding);
  }  

  var config = require('./config.json');
  var sql = require('sql.js');
  var db;
  
  // path
  var env_root = path.resolve('./');
  
  //
  // Ouverture du fichier de la base de données
  //
  function loadDB() {
    try {
      var fileContent = fs.readFileSync(config.dbPath);
      db = new sql.Database(fileContent);
    }
    catch(err) {}
  }
  loadDB();
 
  // GET home page.
  router.get('/', function(req, res) {
    // This file will contain the Angularjs app.
    res.render('index');
  });
   
  // Serve config
  router.get('/api/config', function(req, res) {
    res.json(config);
  });
  
  router.put('/api/save', function(req, res) {
    var obj = {};
    if (req.query.id) {
      if(config.hasOwnProperty(req.query.id) && req.query.value.length < 512){
        config[req.query.id] = decodeURIComponent(req.query.value);
        var buffer = JSON.stringify(config);
        var configPath = path.join(env_root, 'html/server/config.json');
        fs.writeFile(configPath, buffer, function(err) {
          if (!err) {
            if (req.query.id == 'dbPath') {
              loadDB();
            }
          }
          res.json({});
        });
      }
      else {
        res.json({});
      }
    }
    else {
      res.json({});
    }
  });
  
  // Run verification
  router.post('/api/verify', function(req, res) {
    if (req.query.src)
    {
      var reportPath = path.join(path.dirname(config.rulesScript), 'Models');
      var srcPath = decodeURIComponent(req.query.src);
      var rules = config.rules.split(";"); 
      var script = 'constant ENABLED_RULES = new Structure();\nconstant ENABLED_DIAGRAMS = new Structure();\n\ninclude("Pattern.td");\ninclude("DataBase.td");\ninclude("Parse.td");\ninclude("FileData.td");\ninclude("Diagrams.td");\ninclude("Report.td");\n\nconstant:DB_ACCESS.properties.TextFileEnabled = ' + config.embeddedFile + ';\n';
      for (var i = 0; i < rules.length; i++) {
        if (rules[i] !== '') {
          script += 'constant:ENABLED_RULES.' + rules[i] + ' = false;\n';
        }
      }
      script += '\nCleanCppFile();\n\nParse("' + srcPath + '");\n\ninclude("' + config.rulesScript + '");\n\nReviewCode("' + srcPath + '", "' + path.join(reportPath, config.reportModel) + '", "' + config.projectName + '", "' + config.outPath + '");';
      var encoded = iconvlite.encode(script, 'UTF16-LE', {addBOM: true});
      var mainPath = path.join(config.outPath, 'main.td');
      fs.writeFile(mainPath, encoded, function(err) {
        try {
          var line = config.exePath + ' ' + mainPath + ' -module cppbase ' + config.dbPath + ' -v 6';
          console.log(line);
          var cmd = spawn('cmd', ['/C', config.exePath, mainPath, '-module', 'cppbase', config.dbPath, '-v', '6'], { cwd:env_root });

          cmd.stderr.pipe(process.stderr);
          cmd.stdout.pipe(process.stdout);
          cmd.on('exit', function(code){
            loadDB();
            res.json({});
          });
        } 
        catch(exc) {
          console.log('err: ' + exc);
        }
      });
    }
  });
  
  // Run collect debug information
  router.post('/api/debugDB', function(req, res) {
    if (req.query.src)
    {
      var srcPath = decodeURIComponent(req.query.src);
      var script = 'include("Pattern.td");\ninclude("DataBase.td");\ninclude("Parse.td");\ninclude("./Debug/debug.td");\nSourcePath = "' + srcPath + '";\nPdbPath = "' + config.pdbPath + '";\nParse(SourcePath);\nCleanDebug();\nCollectInfo(PdbPath);';
      var encoded = iconvlite.encode(script, 'UTF16-LE', {addBOM: true});
      var mainPath = path.join(config.outPath, 'main.td');
      fs.writeFile(mainPath, encoded, function(err) {
        try {
          var line = config.exePath + ' ' + mainPath + ' -module cppbase ' + config.dbPath + ' -v 6';
          console.log(line);
          var cmd = spawn('cmd', ['/C', config.exePath, mainPath, '-module', 'cppbase', config.dbPath, '-v', '6'], { cwd:env_root });

          cmd.stderr.pipe(process.stderr);
          cmd.stdout.pipe(process.stdout);
          cmd.on('exit', function(code){
            loadDB();
            res.json({});
          });
        } 
        catch(exc) {
          console.log('err: ' + exc);
        }
      });
    }
  });
  
  // Start debug exe
  router.post('/api/startDebug', function(req, res) {
    if (req.body)
    {
      //console.log(req.body.functionName + ' : ' + req.body.functionAddress + ' : ' + req.body.debugStartAddress);
      var srcPath = decodeURIComponent(req.query.src);
      var script = 'include("Pattern.td");\ninclude("DataBase.td");\ninclude("Parse.td");\ninclude("./Debug/debug.td");\nSourcePath = "' + srcPath + '";\nExePath = "' + config.debugPath + '";\ndebugInfo = new Structure();\ndebugInfo.startAddress = ' + req.body.debugStartAddress + ';\ndebugInfo.endAddress = ' + req.body.debugEndAddress + ';\ndebugInfo.variables = new Array()';
      for (var ivar = 0; ivar < req.body.debugVariables.length; ivar++) {
        script =  script + ';\ndebugInfo.variables[' + ivar + '] = ' + req.body.debugVariables[ivar].identifier;
      }
      script =  script + ';\nRunDebug(ExePath, ' + req.body.functionAddress + ', debugInfo);';
      var encoded = iconvlite.encode(script, 'UTF16-LE', {addBOM: true});
      var mainPath = path.join(config.outPath, 'main.td');
      fs.writeFile(mainPath, encoded, function(err) {
        try {
          var line = config.exePath + ' ' + mainPath + ' -module cppbase ' + config.dbPath + ' -v 6';
          console.log(line);
          var cmd = spawn('cmd', ['/C', config.exePath, mainPath, '-module', 'cppbase', config.dbPath, '-v', '6'], { cwd:env_root });

          cmd.stderr.pipe(process.stderr);
          cmd.stdout.pipe(process.stdout);
          cmd.on('exit', function(code){
            loadDB();
            res.json({});
          });
        } 
        catch(exc) {
          console.log('err: ' + exc);
        }
      });
    }
  });
  
  // Run db creation
  router.post('/api/createDB', function(req, res) {
    if (req.query.path)
    {
      var dbPath = decodeURIComponent(req.query.path);
      try {
        var line = '.\\Test\\sqlite3.exe ' + dbPath + ' < .\\Test\\cppbase.sql';
        console.log(line);
        var cmd = spawn('cmd', ['/C', '.\\Test\\sqlite3.exe', dbPath, '<', '.\\Test\\cppbase.sql'], { cwd:env_root });

        cmd.stderr.pipe(process.stderr);
        cmd.stdout.pipe(process.stdout);
        cmd.on('exit', function(code){
          loadDB();
          res.json({});
        });
      } 
      catch(exc) {
        console.log('err: ' + exc);
      }
    }
  });
  
  // Serve Files
  router.get('/api/files', function(req, res) {
    // Select filename
    var files = [];
    if (db) {
      var results = db.exec('SELECT idText, name FROM cppFile;');
      if (results !== null && results.length > 0) {
        var rows = results[0];
        for (var i = 0; i < rows.values.length; i++) {
          files.push({
                      'id': rows.values[i][0],
                      'name': rows.values[i][1]
                    });
          //console.log(files[i].name);
        }
      }
    }
    res.json(files);
  });
  
  // Serve Models
  router.get('/api/models', function(req, res) {
    var files = [];
    var p = req.query.path;
    if (p !== undefined)
    {
      p = decodeURIComponent(p);
      var reportPath = path.join(path.dirname(p), 'Models');
      try {
        var list = fs.readdirSync(reportPath);
        // Read each file
        for (var i = 0; i < list.length; i++) {
          try {
            var stats = fs.statSync(path.join(reportPath, list[i]));
            if (!stats.isDirectory() && list[i].match(/.+\.xml$/) !== null) {
              files.push(list[i]);
            }
          }
          catch (err) {}
        }
      }
      catch (err) {}
    }
    res.json(files);
  });

  // Serve File Content
  router.get('/api/fileContent', function(req, res) {
    var fileId = req.query.id;
    var file = {'id' : fileId,
                'path': '',
                'content':'No content',
                'type':'header',
                'linesCount': 0,
                'errorsCount':0,
                'classesCount':0,
                'enumsCount':0,
                'decMethodsCount':0,
                'defMethodsCount':0,
                'attributesCount':0,
                'macrosCount':0,
                'complexityAvg':0};
    // Select filename
    if (fileId !== undefined && !isNaN(parseInt(fileId)) && fileId != -1)
    {
      var results = db.exec('SELECT c.idText, c.path, c.idType, c.linesCount, errors, classes, enums, methodsDec, methodsDef, attributes, macros, complexities, t.content FROM (' + '(SELECT COUNT(n.rowid) as errors FROM textNotice n WHERE n.idText=' + fileId + ' and n.lengthBlock!=0),' + '(SELECT COUNT(cc.identifier) as classes FROM cppClass cc WHERE cc.idFile=' + fileId + ' and cc.lengthBlock!=0),' + '(SELECT COUNT(ce.identifier) as enums FROM cppEnum ce WHERE ce.idFile=' + fileId + ' and ce.lengthBlock!=0),' + '(SELECT COUNT(cf.identifier) as methodsDec FROM cppFunction cf WHERE cf.idDecFile=' + fileId + ' and cf.lengthDecBlock!=0),' + '(SELECT COUNT(cf.identifier) as methodsDef, AVG(complexity) as complexities FROM cppFunction cf WHERE cf.idDefFile=' + fileId + ' and cf.lengthDefBlock!=0),' + '(SELECT COUNT(ca.identifier) as attributes FROM cppAttribute ca, cppClass cc WHERE cc.idFile=' + fileId + ' and cc.identifier=ca.idClass and ca.lengthBlock!=0),' + '(SELECT COUNT(cm.identifier) as macros FROM cMacro cm WHERE cm.idFile=' + fileId + ' and cm.lengthBlock!=0),' + 'cppFile c, textFile t)' + 'WHERE c.idText=' + fileId + ' and t.rowid=c.idText;');
      
      if (results !== null && results.length > 0){
        var rows = results[0];
        var id = rows.values[0][0];
        file.path = rows.values[0][1];
        if (rows.values[0][12]==='file not available.') {
          try {
            file.content = readFileSync_encoding(rows.values[0][1], 'ISO-8859-1');
          } 
          catch(err) {}
        }
        else {
          file.content = rows.values[0][12];
        }
        if (rows.values[0][2] == 2) {
            file.type = 'source';
        }
        file.linesCount = rows.values[0][3];
        file.errorsCount = rows.values[0][4];
        file.classesCount = rows.values[0][5];
        file.enumsCount = rows.values[0][6];
        file.decMethodsCount = rows.values[0][7];
        file.defMethodsCount = rows.values[0][8];
        file.attributesCount = rows.values[0][9];
        file.macrosCount = rows.values[0][10];
        file.complexityAvg = (rows.values[0][11]===null)?0:(rows.values[0][11]).toFixed(1);
      }
    }
    res.json(file);
  });
  
  // Serve File Content
  router.get('/api/fileDebug', function(req, res) {
    var fileId = req.query.id;
    var file = {'id' : fileId,
                'compilandPath' : '',
                'checksum' : '',
                'debugSymbols': []};
    // Select filename
    if (fileId !== undefined && !isNaN(parseInt(fileId)) && fileId != -1)
    {
      var results = db.exec('SELECT identifier, compilandPath, checksum FROM debugFileInfo WHERE idFile=' + fileId + ';');
      
      if (results !== null && results.length > 0){
        var rows = results[0];
        var id = rows.values[0][0];
        file.compilandPath = rows.values[0][1];
        file.checksum = rows.values[0][2];
        
        results = db.exec('SELECT c.name, d.lineNumber, d.address, d.debugStart, d.debugEnd, d.identifier FROM cppFunction c, debugFunctionInfo d WHERE c.idDefFile=' + fileId + ' and c.lengthDefBlock!=0 and c.identifier=d.idFunction;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (var i = 0; i < rows.values.length; i++) {
            results = db.exec('SELECT dv.identifier, dv.name, dv.category, dv.type, dv.textValue FROM debugVariableInfo dv WHERE dv.idDebugFunction=' + rows.values[i][5] + ';');
            var debugVars = [];
            if (results !== null && results.length > 0){
              var rowVars = results[0];
              for (var j = 0; j < rowVars.values.length; j++) {
                debugVars.push({
                        'identifier': rowVars.values[j][0],
                        'name': rowVars.values[j][1],
                        'category': rowVars.values[j][2],
                        'type': rowVars.values[j][3],
                        'value': rowVars.values[j][4],
                      });
              }
            }
            file.debugSymbols.push({
                        'name': rows.values[i][0],
                        'lineNumber': rows.values[i][1],
                        'address': rows.values[i][2],
                        'debugStart': rows.values[i][3],
                        'debugEnd': rows.values[i][4],
                        'debugVariables': debugVars
                      });
            //console.log(file.debugSymbols[i].name + " " + file.debugSymbols[i].lineNumber + " " + file.debugSymbols[i].address + " " + file.debugSymbols[i].debugStart + " " + file.debugSymbols[i].debugEnd + " " + file.debugSymbols[i].debugVariables[0].name);
          }
        }
      }
    }
    res.json(file);
  });
  
  router.get('/api/filterList', function(req, res) {
    var filterName = req.query.name;
    var fileId = req.query.id;
    var filter = {'name': filterName,
                  'list': []};
    var rows, i;
    // Select filename
    if (filterName !== undefined && fileId !== undefined && !isNaN(parseInt(fileId)) && fileId != -1)
    {
      var results = null;
      if (filterName == 'Errors')
      {
        results = db.exec('SELECT lineNumber, startBlock, lengthBlock, category, description FROM textNotice WHERE idText=' + fileId + ' and lengthBlock!=0 GROUP BY lineNumber ORDER BY ABS(startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': rows.values[i][3],
                        'description': rows.values[i][4]
                      });
            //console.log(filter.list[i].lineNumber + " " + filter.list[i].category);
          }
        }
      }
      else if (filterName == 'Classes')
      {
        results = db.exec('SELECT cc.lineNumber, cc.startBlock, cc.lengthBlock, cc.name, cc.linesCount, methodsCount, attributesCount FROM cppClass cc, (SELECT cc.identifier as aClassIdentifier, COUNT(ca.identifier) as attributesCount FROM cppClass cc LEFT JOIN cppAttribute ca ON ca.idClass=cc.identifier and ca.lengthBlock!=0 WHERE cc.idFile=' + fileId + ' and cc.lengthBlock!=0 GROUP BY cc.identifier), (SELECT cc.identifier as fClassIdentifier, COUNT(cf.identifier) as methodsCount FROM cppClass cc LEFT JOIN cppFunction cf ON cf.idClass=cc.identifier and cf.lengthDecBlock!=0 WHERE cc.idFile=' + fileId + ' and cc.lengthBlock!=0 GROUP BY cc.identifier) WHERE aClassIdentifier=cc.identifier and fClassIdentifier=cc.identifier and cc.idFile=' + fileId + ' and cc.lengthBlock!=0 ORDER BY ABS(cc.startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': 'class ' + rows.values[i][3],
                        'description': ' Lines count: ' + rows.values[i][4] + ', Methods count: ' + rows.values[i][5] + ', Attributes count: ' + rows.values[i][6] + '.'
                      });
          }
        }
      }
      else if (filterName == 'Enumerations') 
      {
        results = db.exec('SELECT lineNumber, startBlock, lengthBlock, name FROM cppEnum WHERE idFile=' + fileId + ' and lengthBlock!=0 ORDER BY ABS(startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': 'enum ' + rows.values[i][3],
                        'description': ''
                      });
          }
        }
      }
      else if (filterName == 'Functions') 
      {
        results = db.exec('SELECT lineNumber, startBlock, lengthBlock, name, complexity, linesCount FROM (SELECT decLineNumber as lineNumber, name, startDecBlock as startBlock, lengthDecBlock as lengthBlock, complexity, linesCount FROM cppFunction WHERE idDecFile=' + fileId + ' and lengthDecBlock!=0 UNION SELECT defLineNumber as lineNumber, name, startDefBlock as startBlock, lengthDefBlock as lengthBlock, complexity, linesCount FROM cppFunction WHERE idDefFile=' + fileId + ' and lengthDefBlock!=0) ORDER BY ABS(startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': 'function ' + rows.values[i][3],
                        'description': ' Complexity: ' + rows.values[i][4] + ', Lines count: ' + rows.values[i][5] + '.'
                      });
          }
        }
      }
      else if (filterName == 'Attributes') 
      {
        results = db.exec('SELECT a.lineNumber, a.startBlock, a.lengthBlock, a.name, a.isConst, a.constValue FROM cppAttribute a, cppClass c WHERE a.idClass=c.identifier and c.idFile=' + fileId + ' and a.lengthBlock!=0 ORDER BY ABS(a.startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': 'attribute ' + rows.values[i][3],
                        'description': (rows.values[i][4] == '1' && rows.values[i][5] !== '')? (rows.values[i][5]): ''
                      });
          }
        }
      }
      else if (filterName == 'Macros') 
      {
        results = db.exec('SELECT lineNumber, startBlock, lengthBlock, name FROM cMacro WHERE idFile=' + fileId + ' and lengthBlock!=0 ORDER BY ABS(startBlock) ASC;');
        if (results !== null && results.length > 0){
          rows = results[0];
          for (i = 0; i < rows.values.length; i++) {
            filter.list.push({
                        'lineNumber': rows.values[i][0],
                        'start': rows.values[i][1],
                        'length': rows.values[i][2],
                        'category': 'macro ' + rows.values[i][3],
                        'description': ''
                      });
          }
        }
      }
    }
    res.json(filter);
  });

  // Serve drives letter
  router.get('/api/filebrowser/drives', function(req, res) {
    var drives = [];
    var letters = ['C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
    for (var i = 0; i < letters.length; i++) {
      var drive = letters[i] + ':\\';
      try {
        var stats = fs.statSync(drive);
        if (stats.isDirectory()) {
          drives.push(drive);
        }
      } 
      catch(err) {}
    }
    res.json(drives);
  });
  
  // Serve the files
  router.get('/api/filebrowser/files', function(req, res) {
    var folders = [];
    var files = [];
    var currentPath;
    if (req.query.id) {
      if (req.query.id == 1) {
        currentPath = path.resolve(process.env.USERPROFILE);
      }
      else if (req.query.id == 2 && req.query.path) {
        currentPath = path.resolve(decodeURIComponent(req.query.path), '..');
      }
      else if (req.query.id == 3 && req.query.path) {
        currentPath = decodeURIComponent(req.query.path);
      }
      try {
        var list = fs.readdirSync(currentPath);
        // Read each file
        for (var i = 0; i < list.length; i++) {
          try {
            var stats = fs.statSync(path.join(currentPath, list[i]));
            if (stats.isDirectory()) {
              folders.push({
                      'path': path.join(currentPath, list[i]),
                      'name': list[i],
                      'isDirectory': stats.isDirectory()
                    });
            }
            else {
              files.push({
                      'path': path.join(currentPath, list[i]),
                      'name': list[i],
                      'isDirectory': stats.isDirectory()
                    });
            }
          }
          catch (err) {}
        }
      }
      catch (err) {}
    }
    res.json({'path': currentPath, 'files': folders.concat(files)});
  });
  
  // Create new folder
  router.post('/api/filebrowser/mkdir', function(req, res) {
    if (req.query.path) {
      var folderPath = decodeURIComponent(req.query.path);
      try {
        fs.mkdirSync(folderPath);
      } 
      catch(err) {}
    }
    res.json({});
  });
 
  module.exports = router;
 
}());