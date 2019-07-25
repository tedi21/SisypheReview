constant VERSION = "3.0.0";
constant ENABLED_RULES = new Structure();
constant ENABLED_DIAGRAMS = new Structure();
constant EXCLUDE_PATHS = constant:excludePath.Split(";");

include("Pattern.td");
include("DataBase.td");
include("Parse.td");
include("FileData.td");
include("Diagrams.td");
include("Report.td");

/* Ajout des règles de codage à vérifier */
include(".\CodingRules\CppCustom\Review.td");