function IsIdentifierOfConnectedClass(value)
	/*return*/ (value.Identifier == identifier);
endfunction

function IsConnectedClass(connectedClasses, identifier)
	predicate = function:IsIdentifierOfConnectedClass;
	predicate.Variables("identifier") = identifier;
	i = connectedClasses.Find(predicate);
	/*return*/ (i == #connectedClasses);
endfunction

function GetClassIdentifier(className)
	identifier = 0;
	classes = constant:DB_ACCESS.cppClass.GetManyCppClasss("name='" & className & "'");
	if #classes > 0 then
		identifier = classes[0].Identifier;
	endif
	/*return*/ identifier;
endfunction

function GetClassGroup(connectedClasses, links, noConnectedClasses)
	/* Définit l'ensemble des héritages */
	inheritances = constant:DB_ACCESS.cppInheritance.GetAllCppInheritances();
	iInheritance = 0;
	iConnected = 0;
	while iInheritance < #inheritances do
		constant:DB_ACCESS.cppInheritance.FillDerived(inheritances[iInheritance]);
		connectedClasses[iConnected] = new Structure();
		connectedClasses[iConnected].Identifier = GetClassIdentifier(inheritances[iInheritance].BaseClassName);
		connectedClasses[iConnected].Name = inheritances[iInheritance].BaseClassName;
		iConnected.Increment();
		
		connectedClasses[iConnected] = new Structure();
		connectedClasses[iConnected].Identifier = inheritances[iInheritance].Derived.Identifier;
		connectedClasses[iConnected].Name = inheritances[iInheritance].Derived.Name;
		iConnected.Increment();
		
		links[iInheritance] = new Structure();
		links[iInheritance].BaseIdentifier = GetClassIdentifier(inheritances[iInheritance].BaseClassName);
		links[iInheritance].DerivedIdentifier = inheritances[iInheritance].Derived.Identifier;
		iInheritance.Increment();
	endwhile
	
	/* Définit l'ensemble des classes */
	classes = constant:DB_ACCESS.cppClass.GetAllCppClasss();
	iClass = 0;
	iGroup = 0;
	iNoConnected = 0;
	while iClass < #classes do
		if IsConnectedClass(connectedClasses, classes[iClass].Identifier) then
			if iNoConnected >= 7 then
				iNoConnected = 0;
				iGroup.Increment();
			endif
			if iNoConnected == 0 then
				noConnectedClasses[iGroup] = new Array();
			endif
			noConnectedClasses[iGroup][iNoConnected] = new Structure();
			noConnectedClasses[iGroup][iNoConnected].Identifier = classes[iClass].Identifier;
			noConnectedClasses[iGroup][iNoConnected].Name = classes[iClass].Name;
			iNoConnected.Increment();
		endif
		iClass.Increment();
	endwhile
endfunction

function WriteClassDiagram(outputPath, name, classes, links)
	/* Création du fichier dot */
	file = new File(outputPath & "/" & name & ".dot", "OVERWRITE", "UTF8");
	file << ("digraph " & DblQuotes & "Graphical Class Hierarchy" & DblQuotes);
	file << CrLf;
	file << "{";
	file << CrLf;
	file << ("edge [fontname=" & DblQuotes & "Helvetica" & DblQuotes & ",fontsize=" & DblQuotes & "10" & DblQuotes & ",labelfontname=" & DblQuotes & "Helvetica" & DblQuotes & ",labelfontsize=" & DblQuotes & "10" & DblQuotes & "];");
	file << CrLf;
	file << ("node [fontname=" & DblQuotes & "Helvetica" & DblQuotes & ",fontsize=" & DblQuotes & "10" & DblQuotes & ",shape=record];");
	file << CrLf;
	file << ("rankdir=" & DblQuotes & "TB" & DblQuotes & ";");
	file << CrLf;
	
	/* Définit l'ensemble des classes */
	iClass = 0;
	while iClass < #classes do
		file << ("Node" & classes[iClass].Identifier & " [label=" & DblQuotes & classes[iClass].Name & DblQuotes & ",height=0.2,width=0.4,color=" & DblQuotes & "black" & DblQuotes & ", fillcolor=" & DblQuotes & "white" & DblQuotes & ", style=" & DblQuotes & "filled" & DblQuotes & "];");
		file << CrLf;
		iClass.Increment();
	endwhile
	
	/* Définit l'ensemble des héritages */
	iLink = 0;
	while iLink < #links do
		file << ("Node" & links[iLink].BaseIdentifier & " -> Node" & links[iLink].DerivedIdentifier & " [dir=" & DblQuotes & "back" & DblQuotes & ",color=" & DblQuotes & "midnightblue" & DblQuotes & ",fontsize=" & DblQuotes & "10" & DblQuotes & ",style=" & DblQuotes & "solid" & DblQuotes & ",fontname=" & DblQuotes & "Helvetica" & DblQuotes & "];");
		file << CrLf;
		iLink.Increment();
	endwhile
	
	file << "}";
	file = null;
	
	/* Appel à graphviz pour générer le graph */
	command = ("dot -Tpng " & outputPath & "/") & (name & ".dot") & (" > " & outputPath & "/") & (name & ".png");
	system(command);
	
	/* Suppresssion du fichier dot */
	directory = new Folder(outputPath);
	directory.Remove(name & ".dot");
endfunction

function CreateClassDiagram(outputPath)
	connectedClasses = new Array();
	links = new Array();
	noConnectedClasses = new Array();
	GetClassGroup(connectedClasses, links, noConnectedClasses);
	
	fileName = new Array();
	fileName[0] = "ClassDiagram0.png";
	/* Crée le diagramme avec les relations d'héritage */
	WriteClassDiagram(outputPath, "ClassDiagram0", connectedClasses, links);
	
	iGroup = 0;
	while iGroup < #noConnectedClasses do
		fileName[(iGroup + 1)] = "ClassDiagram" & (iGroup + 1) & ".png";
		/* Crée les diagrammes avec les classes seules */
		WriteClassDiagram(outputPath, "ClassDiagram" & (iGroup + 1), noConnectedClasses[iGroup], new Array());
		iGroup.Increment();
	endwhile
	
	/* return */ fileName;
endfunction
