constant GIT = new Structure();

function InitGit(path)
  constant:GIT.system = new Git();
  constant:GIT.init = constant:GIT.system.IsType("Git");
  if constant:GIT.init then
    constant:GIT.repository = new GitRepository();
    constant:GIT.opened = constant:GIT.system.OpenRepository(constant:GIT.repository, path);
    constant:GIT.blame = new GitBlame();
    constant:GIT.fileBlamed = -1;
    constant:GIT.blamed = false;
  else
    constant:GIT.opened = false;
    constant:GIT.fileBlamed = -1;
    constant:GIT.blamed = false;
  endif
endfunction

function ReleaseGit()
  constant:GIT.blame = null;
  constant:GIT.repository = null;
  constant:GIT.system = null;
  constant:GIT.opened = false;
  constant:GIT.fileBlamed = -1;
  constant:GIT.blamed = false;
endfunction

function IsFileGitUntracked(path)
  res = true;
  if constant:GIT.opened then
    res = constant:GIT.repository.IsUntracked(path);
  endif
  /*return*/ res;
endfunction

function GitBlameFile(fileData)
  if constant:GIT.opened && (fileData.Properties.Identifier != constant:GIT.fileBlamed) then
    constant:GIT.fileBlamed = fileData.Properties.Identifier;
    constant:GIT.blamed = constant:GIT.repository.Blame(constant:GIT.blame, fileData.Properties.Path);
  endif
endfunction

function FillBlameInfo(error)
  if constant:GIT.blamed then
    if constant:GIT.blame.Line(error.LineNumber) then
      str = "";
      n = 0;
      if constant:GIT.blame.GetCommitId(str) then
        error.CommitHash = str;
      endif
      if constant:GIT.blame.GetCommitAuthor(str) then
        error.CommitAuthor = str;
      endif
      if constant:GIT.blame.GetCommitDate(str) then
        error.CommitDate = str;
      endif
      if constant:GIT.blame.GetCommitLine(n) then
        error.CommitLine = n;
      endif
    endif
  endif
endfunction
