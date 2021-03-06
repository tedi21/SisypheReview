/*
 * word_wrapper.h
 *
 *
 * @date 02-08-2019
 * @author Teddy DIDE
 * @version 1.00
 * Word Wrapper generated by gensources. Allows to control MS Word.
 */

#ifndef _WORD_WRAPPER_H_
#define _WORD_WRAPPER_H_

#include <windows.h>
#include <string>

namespace word
{
	/* WdGoToItem*/
	enum WdGoToItem
	{
		wdGoToHeading = 11,
		wdGoToLine = 3,
		wdGoToPage = 1,
		wdGoToTable = 2,
		wdGoToComment = 6,
		wdGoToSection = 0
	};

	/* WdGoToDirection*/
	enum WdGoToDirection
	{
		wdGoToAbsolute = 1,
		wdGoToRelative = 2,
		wdGoToFirst = 1,
		wdGoToLast = -1,
		wdGoToNext = 2,
		wdGoToPrevious = 3
	};

	/* WdBuiltinStyle*/
	enum WdBuiltinStyle
	{
		wdStyleHeading1 = -2,
		wdStyleHeading2 = -3,
		wdStyleHeading3 = -4,
		wdStyleHeading4 = -5,
		wdStyleHeading5 = -6,
		wdStyleHeading6 = -7,
		wdStyleHeading7 = -8,
		wdStyleHeading8 = -9,
		wdStyleHeading9 = -10
	};

	/* WdCollapseDirection*/
	enum WdCollapseDirection
	{
		wdCollapseEnd = 0,
		wdCollapseStart = 1
	};

	/* WdSaveOptions*/
	enum WdSaveOptions
	{
		wdDoNotSaveChanges = 0,
		wdSaveChanges = -1,
		wdPromptToSaveChanges = -2
	};

	/* WdOriginalFormat*/
	enum WdOriginalFormat
	{
		wdOriginalDocumentFormat = 1,
		wdPromptUser = 2,
		wdWordDocument = 0
	};

	/* WdCompareTarget*/
	enum WdCompareTarget
	{
		wdCompareTargetCurrent = 1,
		wdCompareTargetNew = 2,
		wdCompareTargetSelected = 0
	};

	/* WdSaveFormat*/
	enum WdSaveFormat
	{
		wdFormatDocument = 0,
		wdFormatDOSText = 4,
		wdFormatDOSTextLineBreaks = 5,
		wdFormatEncodedText = 7,
		wdFormatFilteredHTML = 10,
		wdFormatHTML = 8,
		wdFormatRTF = 6,
		wdFormatTemplate = 1,
		wdFormatText = 2,
		wdFormatTextLineBreaks = 3,
		wdFormatUnicodeText = 7,
		wdFormatWebArchive = 9,
		wdFormatXML = 11,
		wdFormatDocument97 = 0,
		wdFormatDocumentDefault = 16,
		wdFormatPDF = 17,
		wdFormatTemplate97 = 1,
		wdFormatXMLDocument = 12,
		wdFormatXMLDocumentMacroEnabled = 13,
		wdFormatXMLTemplate = 14,
		wdFormatXMLTemplateMacroEnabled = 15,
		wdFormatXPS = 18
	};

	/* WdMergeTarget*/
	enum WdMergeTarget
	{
		wdMergeTargetCurrent = 1,
		wdMergeTargetNew = 2,
		wdMergeTargetSelected = 0
	};

	/* WdUseFormattingFrom*/
	enum WdUseFormattingFrom
	{
		wdFormattingFromCurrent = 0,
		wdFormattingFromPrompt = 2,
		wdFormattingFromSelected = 1
	};

	/* Specifies how Microsoft Word resizes a table when the AutoFit feature is used.*/
	enum WdAutoFitBehavior
	{
		wdAutoFitFixed = 0,
		wdAutoFitContent = 1,
		wdAutoFitWindow = 2
	};

	enum MsoControlType
	{
		msoControlButton = 1,
		msoControlEdit = 2,
		msoControlDropdown = 3,
		msoControlComboBox = 4,
		msoControlPopup = 10
	};

	class Document;
	class Documents;
	class Selection;
	class Options;
	class Template;
	class CommandBars;

	/* Represents the entire Microsoft Word application. */
	class Application
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Application();
		// Constructor
		Application(IDispatch* pApplication, bool pAddRef = false);
		// Copy Constructor
		Application(const Application& copy);
		// Destructor
		~Application();
		// Assignment operator
		Application& operator=(const Application& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Document object that represents the active document. */
		Document getActiveDocument() const;
		/* Returns a Documents collection that represents all the open documents. */
		Documents getDocuments() const;
		/* Determines if the specified object is visible. This property returns True if the specified object is visible, and False if not. */
		bool getVisible() const;
		void setVisible(bool visible);
		/* Determines if screen updating is turned on. Returns True if screen updating is turned on, and False if not. */
		bool getScreenUpdating() const;
		void setScreenUpdating(bool screenupdating);
		/* Returns the Selection object that represents a selected range or the insertion point. */
		Selection getSelection() const;
		/* Returns an Options object that represents application settings in Microsoft Word.*/
		Options getOptions() const;
		/* */
		IDispatch* getCustomizationContext() const;
		void setCustomizationContext(IDispatch* customizationcontext);
		Template getNormalTemplate() const;
		CommandBars getCommandBars() const;
		
		
		/* Quits Microsoft Word and optionally saves or routes the open documents. */
		void Quit();
		
	};

	class Document;
	class Document;

	/* A collection of all the Document objects that are currently open in Word.*/
	class Documents
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Documents();
		// Constructor
		Documents(IDispatch* pDocuments, bool pAddRef = false);
		// Copy Constructor
		Documents(const Documents& copy);
		// Destructor
		~Documents();
		// Assignment operator
		Documents& operator=(const Documents& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection.*/
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		Document Item(int index);
		/* Opens the specified document and adds it to the Documents collection. */
		Document Open(const std::basic_string<TCHAR>& filename, bool confirmconversions, bool readonly, bool addtorecentfiles);
		/* Closes the specified document or documents. */
		void Close(WdSaveOptions savechanges, WdOriginalFormat originalformat, bool routedocument);
		/* Saves all the documents in the Documents collection. */
		void Save();
		
	};

	class Paragraphs;
	class TablesOfContents;
	class Fields;
	class Tables;
	class Window;
	class Range;
	class Range;

	/* Represents a document. */
	class Document
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Document();
		// Constructor
		Document(IDispatch* pDocument, bool pAddRef = false);
		// Copy Constructor
		Document(const Document& copy);
		// Destructor
		~Document();
		// Assignment operator
		Document& operator=(const Document& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Gets the name of the document, including the drive or Web path. */
		std::basic_string<TCHAR> getFullName() const;
		/* Returns a Paragraphs collection that represents all the paragraphs in the specified document. */
		Paragraphs getParagraphs() const;
		/* Gets a TablesOfContents collection that represents the tables of contents in the document.*/
		TablesOfContents getTablesOfContents() const;
		/* Gets a read-only Fields collection that contains the fields in the main text story.*/
		Fields getFields() const;
		/* Gets a Tables collection that represents all the tables in the document.*/
		Tables getTables() const;
		/* Returns a Window object that represents the active window. */
		Window getActiveWindow() const;
		/* Returns a Range object that represents the main document story.*/
		Range getContent() const;
		/* Determines if the specified document or template hasn't changed since it was last saved. */
		bool getSaved() const;
		void setSaved(bool saved);
		
		
		/* Saves the document. If the document has not been saved before, the Save As dialog box prompts the user for a file name. */
		void Save();
		/* Accepts all tracked changes in the document.*/
		void AcceptAllRevisions();
		/* Returns a Microsoft.Office.Interop.Word.Range that represents the start position of the specified item, such as a page, bookmark, or field.*/
		Range GoTo(WdGoToItem what, WdGoToDirection which, int count);
		/* Closes the document.*/
		void Close(WdSaveOptions savechanges, WdOriginalFormat originalformat, bool routedocument);
		/* Displays revision marks that indicate where the specified document differs from another document. */
		void Compare(const std::basic_string<TCHAR>& name, const std::basic_string<TCHAR>& authorname, WdCompareTarget comparetarget, bool detectformatchanges, bool ignoreallcomparisonwarnings, bool addtorecentfiles, bool removepersonalinformation, bool removedateandtime);
		/* Merges the changes marked with revision marks from one document to another.*/
		void Merge(const std::basic_string<TCHAR>& filename, WdMergeTarget mergetarget, bool detectformatchanges, WdUseFormattingFrom useformattingfrom, bool addtorecentfiles);
		/* Saves the specified document with a new name or format. Some of the arguments for this method correspond to the options in the Save Asdialog box (File menu). */
		void SaveAs(const std::basic_string<TCHAR>& filename, WdSaveFormat fileformat);
		
	};

	class Paragraph;

	/* A collection of Paragraph objects in a selection, range, or document. */
	class Paragraphs
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Paragraphs();
		// Constructor
		Paragraphs(IDispatch* pParagraphs, bool pAddRef = false);
		// Copy Constructor
		Paragraphs(const Paragraphs& copy);
		// Destructor
		~Paragraphs();
		// Assignment operator
		Paragraphs& operator=(const Paragraphs& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection.*/
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		Paragraph Item(int index);
		
	};

	class Range;
	class Paragraph;

	/* Represents a single paragraph in a selection, range, or document. */
	class Paragraph
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Paragraph();
		// Constructor
		Paragraph(IDispatch* pParagraph, bool pAddRef = false);
		// Copy Constructor
		Paragraph(const Paragraph& copy);
		// Destructor
		~Paragraph();
		// Assignment operator
		Paragraph& operator=(const Paragraph& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object.*/
		Range getRange() const;
		/* Returns or sets the style for the specified object. */
		int getStyle() const;
		void setStyle(int style);
		
		
		/* Returns a Paragraph object that represents the next paragraph. */
		Paragraph Next(int count);
		
	};

	class TableOfContents;

	/* A collection of TableOfContents objects that represent the tables of contents in a document. */
	class TablesOfContents
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		TablesOfContents();
		// Constructor
		TablesOfContents(IDispatch* pTablesOfContents, bool pAddRef = false);
		// Copy Constructor
		TablesOfContents(const TablesOfContents& copy);
		// Destructor
		~TablesOfContents();
		// Assignment operator
		TablesOfContents& operator=(const TablesOfContents& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		TableOfContents Item(int index);
		
	};

	class Range;
	class HeadingStyles;

	/* Represents a single table of contents in a document. */
	class TableOfContents
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		TableOfContents();
		// Constructor
		TableOfContents(IDispatch* pTableOfContents, bool pAddRef = false);
		// Copy Constructor
		TableOfContents(const TableOfContents& copy);
		// Destructor
		~TableOfContents();
		// Assignment operator
		TableOfContents& operator=(const TableOfContents& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object. */
		Range getRange() const;
		/* True if Table of Contents Entry (TC) fields are used to create a table of contents. */
		bool getUseFields() const;
		void setUseFields(bool usefields);
		/* True if built-in heading styles are used to create a table of contents. */
		bool getUseHeadingStyles() const;
		void setUseHeadingStyles(bool useheadingstyles);
		/* Returns a HeadingStyles object that represents additional styles used to compile a table of contents (styles other than the Heading 1 � Heading 9 styles). */
		HeadingStyles getHeadingStyles() const;
		
		
		/* Updates the entries shown in the specified table of contents. */
		void Update();
		
	};

	class Tables;
	class Range;
	class Range;
	class Range;
	class Range;
	class Range;

	/* Represents a contiguous area in a document. */
	class Range
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Range();
		// Constructor
		Range(IDispatch* pRange, bool pAddRef = false);
		// Copy Constructor
		Range(const Range& copy);
		// Destructor
		~Range();
		// Assignment operator
		Range& operator=(const Range& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns or sets the text in the specified range. */
		std::basic_string<TCHAR> getText() const;
		void setText(const std::basic_string<TCHAR>& text);
		/* Returns a Tables collection that represents all the tables in the specified range. */
		Tables getTables() const;
		/* Returns a String that represents the XML text in the specified object. */
		std::basic_string<TCHAR> getXML() const;
		
		
		/* Returns a Range object that represents the start position of the specified item, such as a page, bookmark, or field. */
		Range GoTo(WdGoToItem what, WdGoToDirection which, int count);
		/* Returns a Range object that refers to the start position of the next item or location specified by the What argument. */
		Range GoToNext(WdGoToItem what);
		/* Returns a Range object that refers to the start position of the previous item or location specified by the What argument. */
		Range GoToPrevious(WdGoToItem what);
		/* Determines if the range to which the method is applied is contained in the specified range. */
		bool InRange(Range const& other);
		/* Returns a Range object that represents the specified unit relative to the specified range. */
		Range Next(int unit, int count);
		
	};

	class Range;

	/* Represents a single table cell.*/
	class Cell
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Cell();
		// Constructor
		Cell(IDispatch* pCell, bool pAddRef = false);
		// Copy Constructor
		Cell(const Cell& copy);
		// Destructor
		~Cell();
		// Assignment operator
		Cell& operator=(const Cell& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object.*/
		Range getRange() const;
		
		
		
	};

	class Table;

	/* A collection of Table objects that represent the tables in a selection, range, or document. */
	class Tables
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Tables();
		// Constructor
		Tables(IDispatch* pTables, bool pAddRef = false);
		// Copy Constructor
		Tables(const Tables& copy);
		// Destructor
		~Tables();
		// Assignment operator
		Tables& operator=(const Tables& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		Table Item(int index);
		
	};

	class Range;
	class Rows;
	class Columns;
	class Cell;

	/* Represents a single table. */
	class Table
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Table();
		// Constructor
		Table(IDispatch* pTable, bool pAddRef = false);
		// Copy Constructor
		Table(const Table& copy);
		// Destructor
		~Table();
		// Assignment operator
		Table& operator=(const Table& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object. */
		Range getRange() const;
		/* Returns a Rows collection that represents all the table rows in a table. */
		Rows getRows() const;
		/* Returns a Columns collection that represents all the table columns in the table.*/
		Columns getColumns() const;
		
		
		/* Returns a Cell object that represents a cell in a table. */
		Cell GetCell(int column, int row);
		/* Determines how Microsoft Word resizes a table when the AutoFit feature is used.*/
		void AutoFitBehavior(WdAutoFitBehavior behavior);
		
	};

	class Row;
	class Row;
	class Row;

	/* A collection of Row objects that represent the table rows in the specified selection, range, or table.*/
	class Rows
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Rows();
		// Constructor
		Rows(IDispatch* pRows, bool pAddRef = false);
		// Copy Constructor
		Rows(const Rows& copy);
		// Destructor
		~Rows();
		// Assignment operator
		Rows& operator=(const Rows& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		/* Returns a Row object that represents the first item in the Rows collection. */
		Row getFirst() const;
		/* Returns a Row object that represents the last item in the Rows collection.*/
		Row getLast() const;
		
		
		/* Returns an individual object in a collection. */
		Row Item(int index);
		
	};

	class Range;
	class Cells;

	/* Represents a row in a table. */
	class Row
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Row();
		// Constructor
		Row(IDispatch* pRow, bool pAddRef = false);
		// Copy Constructor
		Row(const Row& copy);
		// Destructor
		~Row();
		// Assignment operator
		Row& operator=(const Row& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object. */
		Range getRange() const;
		/* Returns a Cells collection that represents the table cells in a column, row, selection, or range. */
		Cells getCells() const;
		/* Returns a value that represents the position of an item in a collection. */
		int getIndex() const;
		
		
		
	};

	class Cell;

	/* A collection of Cell objects in a table column, table row, selection, or range.*/
	class Cells
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Cells();
		// Constructor
		Cells(IDispatch* pCells, bool pAddRef = false);
		// Copy Constructor
		Cells(const Cells& copy);
		// Destructor
		~Cells();
		// Assignment operator
		Cells& operator=(const Cells& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		Cell Item(int index);
		
	};

	class Field;

	/* A collection of Field objects that represent all the fields in a selection, range, or document.*/
	class Fields
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Fields();
		// Constructor
		Fields(IDispatch* pFields, bool pAddRef = false);
		// Copy Constructor
		Fields(const Fields& copy);
		// Destructor
		~Fields();
		// Assignment operator
		Fields& operator=(const Fields& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		Field Item(int index);
		
	};


	/* Represents a field. The Field object is a member of the Fields collection. The Fields collection represents the fields in a selection, range, or document. */
	class Field
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Field();
		// Constructor
		Field(IDispatch* pField, bool pAddRef = false);
		// Copy Constructor
		Field(const Field& copy);
		// Destructor
		~Field();
		// Assignment operator
		Field& operator=(const Field& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the field type. */
		int getType() const;
		/* Returns or sets data in an ADDIN field. */
		std::basic_string<TCHAR> getData() const;
		void setData(const std::basic_string<TCHAR>& data);
		
		
		/* Updates the result of the field object. */
		bool Update();
		/* Clicks the specified field. */
		void DoClick();
		
	};

	class HeadingStyle;

	/* A collection of HeadingStyle objects that represent the styles used to compile a table of figures or table of contents. */
	class HeadingStyles
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		HeadingStyles();
		// Constructor
		HeadingStyles(IDispatch* pHeadingStyles, bool pAddRef = false);
		// Copy Constructor
		HeadingStyles(const HeadingStyles& copy);
		// Destructor
		~HeadingStyles();
		// Assignment operator
		HeadingStyles& operator=(const HeadingStyles& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		
		
		/* Returns an individual object in a collection. */
		HeadingStyle Item(int index);
		
	};


	/* Represents a style used to build a table of contents or figures. */
	class HeadingStyle
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		HeadingStyle();
		// Constructor
		HeadingStyle(IDispatch* pHeadingStyle, bool pAddRef = false);
		// Copy Constructor
		HeadingStyle(const HeadingStyle& copy);
		// Destructor
		~HeadingStyle();
		// Assignment operator
		HeadingStyle& operator=(const HeadingStyle& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns or sets the level for the heading style in a table of contents or table of figures. */
		short getLevel() const;
		void setLevel(short level);
		/* Returns or sets the style for the specified object. */
		int getStyle() const;
		void setStyle(int style);
		
		
		
	};

	class Range;
	class Paragraphs;
	class Tables;
	class Characters;
	class Find;
	class Sentences;
	class Words;
	class Range;
	class Range;
	class Range;

	/* Represents the current selection in a window or pane. */
	class Selection
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Selection();
		// Constructor
		Selection(IDispatch* pSelection, bool pAddRef = false);
		// Copy Constructor
		Selection(const Selection& copy);
		// Destructor
		~Selection();
		// Assignment operator
		Selection& operator=(const Selection& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Range object that represents the portion of a document that's contained in the specified object. */
		Range getRange() const;
		/* Returns a Paragraphs collection that represents all the paragraphs in the specified selection. */
		Paragraphs getParagraphs() const;
		/* Returns or sets the starting character position of a selection.*/
		int getStart() const;
		void setStart(int start);
		/* Returns or sets the ending character position of a selection. */
		int getEnd() const;
		void setEnd(int end);
		/* Returns a Tables collection that represents all the tables in the specified selection.*/
		Tables getTables() const;
		/* Returns the selection type. */
		int getType() const;
		/* Returns or sets the text in the specified selection. */
		std::basic_string<TCHAR> getText() const;
		void setText(const std::basic_string<TCHAR>& text);
		/* Returns or sets the style for the specified object. */
		int getStyle() const;
		void setStyle(int style);
		/* Returns a Characters collection that represents the characters in a selection. */
		Characters getCharacters() const;
		/* Returns a Find object that contains the criteria for a find operation. */
		Find getFind() const;
		/* Returns a Sentences collection that represents all the sentences in the selection. */
		Sentences getSentences() const;
		/* Returns a Words collection that represents all the words in a selection.*/
		Words getWords() const;
		
		
		/* Returns a Range object that represents the start position of the specified item, such as a page, bookmark, or field. */
		Range GoTo(WdGoToItem what, WdGoToDirection which, int count);
		/* Returns a Range object that refers to the start position of the next item or location specified by the What argument. */
		Range GoToNext(WdGoToItem what);
		/* Returns a Range object that refers to the start position of the previous item or location specified by the What argument. */
		Range GoToPrevious(WdGoToItem what);
		/* Moves the start position of the specified selection. */
		int MoveStart(int unit, int count);
		/* Moves the ending character position of a selection. */
		int MoveEnd(int unit, int count);
		/* Collapses a selection to the starting or ending position. */
		void Collapse(WdCollapseDirection direction);
		
	};

	class Range;
	class Range;
	class Range;

	/* A collection of characters in a selection, range, or document. */
	class Characters
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Characters();
		// Constructor
		Characters(IDispatch* pCharacters, bool pAddRef = false);
		// Copy Constructor
		Characters(const Characters& copy);
		// Destructor
		~Characters();
		// Assignment operator
		Characters& operator=(const Characters& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		/* Gets a Range object that represents the first character in a document. */
		Range getFirst() const;
		/* Gets a Range object that represents the last character, word, or sentence in a document. */
		Range getLast() const;
		
		
		/* Returns an individual object in a collection. */
		Range Item(int index);
		
	};


	/* Represents the criteria for a find operation. */
	class Find
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Find();
		// Constructor
		Find(IDispatch* pFind, bool pAddRef = false);
		// Copy Constructor
		Find(const Find& copy);
		// Destructor
		~Find();
		// Assignment operator
		Find& operator=(const Find& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns or sets the style for the specified object. */
		int getStyle() const;
		void setStyle(int style);
		/* Returns or sets the text to find or replace in the specified range or selection. */
		std::basic_string<TCHAR> getText() const;
		void setText(const std::basic_string<TCHAR>& text);
		/* Determines if the text to find contains wildcards. */
		bool getMatchWildcards() const;
		void setMatchWildcards(bool matchwildcards);
		/* Determines if the find operation searches forward through the document. */
		bool getForward() const;
		void setForward(bool forward);
		/* Determines if the search for the specified object has produced a match. */
		bool getFound() const;
		/* Determines if the find operation is case-sensitive. */
		bool getMatchCase() const;
		void setMatchCase(bool matchcase);
		
		
		/* Removes text and paragraph formatting from a selection or from the formatting specified in a find or replace operation. */
		void ClearFormatting();
		/* Runs the specified find operation. */
		bool Execute();
		
	};

	class Range;
	class Range;
	class Range;

	/* A collection of words in a selection, range, or document. */
	class Words
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Words();
		// Constructor
		Words(IDispatch* pWords, bool pAddRef = false);
		// Copy Constructor
		Words(const Words& copy);
		// Destructor
		~Words();
		// Assignment operator
		Words& operator=(const Words& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		/* Returns a Range object that represents the first word in a document, selection or range. */
		Range getFirst() const;
		/* Gets a Range object that represents the last character, word, or sentence in a document. */
		Range getLast() const;
		
		
		/* Returns an individual object in a collection. */
		Range Item(int index);
		
	};

	class Range;
	class Range;
	class Range;

	/* A collection of Range objects that represent all the sentences in a selection, range, or document. There is no Sentence object. */
	class Sentences
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Sentences();
		// Constructor
		Sentences(IDispatch* pSentences, bool pAddRef = false);
		// Copy Constructor
		Sentences(const Sentences& copy);
		// Destructor
		~Sentences();
		// Assignment operator
		Sentences& operator=(const Sentences& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		/* Returns a Range object that represents the first sentence, word, or character in a document, selection or range.*/
		Range getFirst() const;
		/* Returns a Range object that represents the last character, word, or sentence in a document, selection, or range.*/
		Range getLast() const;
		
		
		/* Returns an individual object in a collection. */
		Range Item(int index);
		
	};

	class Column;
	class Column;
	class Column;

	/* A collection of Column objects that represent the columns in a table. */
	class Columns
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Columns();
		// Constructor
		Columns(IDispatch* pColumns, bool pAddRef = false);
		// Copy Constructor
		Columns(const Columns& copy);
		// Destructor
		~Columns();
		// Assignment operator
		Columns& operator=(const Columns& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection. */
		int getCount() const;
		/* Returns a Column object that represents the first item in the Columns collection. */
		Column getFirst() const;
		/* Returns a Column object that represents the last item in the Columns collection.*/
		Column getLast() const;
		
		
		/* Returns an individual object in a collection. */
		Column Item(int index);
		
	};

	class Cells;

	/* Represents a single table column. The Column object is a member of the Columns collection. */
	class Column
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Column();
		// Constructor
		Column(IDispatch* pColumn, bool pAddRef = false);
		// Copy Constructor
		Column(const Column& copy);
		// Destructor
		~Column();
		// Assignment operator
		Column& operator=(const Column& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a Cells collection that represents the table cells in a column. */
		Cells getCells() const;
		/* Returns a value that represents the position of an item in a collection. */
		int getIndex() const;
		
		
		
	};


	/* Represents application and document options in Microsoft Word. Many of the properties for the Options object correspond to items in the Options dialog box (Tools menu). */
	class Options
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Options();
		// Constructor
		Options(IDispatch* pOptions, bool pAddRef = false);
		// Copy Constructor
		Options(const Options& copy);
		// Destructor
		~Options();
		// Assignment operator
		Options& operator=(const Options& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* True if Microsoft Word repaginates documents in the background. */
		bool getPagination() const;
		void setPagination(bool pagination);
		
		
		
	};

	class View;

	/* Represents a window.*/
	class Window
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Window();
		// Constructor
		Window(IDispatch* pWindow, bool pAddRef = false);
		// Copy Constructor
		Window(const Window& copy);
		// Destructor
		~Window();
		// Assignment operator
		Window& operator=(const Window& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a View object that represents the view for the specified window.*/
		View getView() const;
		/* True if the specified object is visible. */
		bool getVisible() const;
		void setVisible(bool visible);
		
		
		
	};


	/* Contains the view attributes (show all, field shading, table gridlines, and so on) for a window or pane.*/
	class View
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		View();
		// Constructor
		View(IDispatch* pView, bool pAddRef = false);
		// Copy Constructor
		View(const View& copy);
		// Destructor
		~View();
		// Assignment operator
		View& operator=(const View& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns or sets the view type.*/
		int getType() const;
		void setType(int type);
		
		
		
	};


	/* Represents a document template.*/
	class Template
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		Template();
		// Constructor
		Template(IDispatch* pTemplate, bool pAddRef = false);
		// Copy Constructor
		Template(const Template& copy);
		// Destructor
		~Template();
		// Assignment operator
		Template& operator=(const Template& copy);
		// Cast operator
		operator IDispatch*() const;
		
		
		
		
	};

	class CommandBar;

	/* A collection of CommandBar objects that represent the command bars in the container application.*/
	class CommandBars
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		CommandBars();
		// Constructor
		CommandBars(IDispatch* pCommandBars, bool pAddRef = false);
		// Copy Constructor
		CommandBars(const CommandBars& copy);
		// Destructor
		~CommandBars();
		// Assignment operator
		CommandBars& operator=(const CommandBars& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection.*/
		int getCount() const;
		
		/* Returns an individual object in a collection. */
		CommandBar getItem(const std::basic_string<TCHAR>& id) const;
		
		
	};

	class CommandBarControls;

	/* Represents a command bar in the container application.*/
	class CommandBar
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		CommandBar();
		// Constructor
		CommandBar(IDispatch* pCommandBar, bool pAddRef = false);
		// Copy Constructor
		CommandBar(const CommandBar& copy);
		// Destructor
		~CommandBar();
		// Assignment operator
		CommandBar& operator=(const CommandBar& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns a CommandBarControls object that represents all the controls on a command bar or pop-up control. */
		CommandBarControls getControls() const;
		
		
		
	};

	class CommandBarControl;
	class CommandBarControl;

	/* A collection of CommandBarControl objects that represent the command bar controls on a command bar.*/
	class CommandBarControls
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		CommandBarControls();
		// Constructor
		CommandBarControls(IDispatch* pCommandBarControls, bool pAddRef = false);
		// Copy Constructor
		CommandBarControls(const CommandBarControls& copy);
		// Destructor
		~CommandBarControls();
		// Assignment operator
		CommandBarControls& operator=(const CommandBarControls& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns the number of items in the specified collection.*/
		int getCount() const;
		
		/* Returns an individual object in a collection. */
		CommandBarControl getItem(int id) const;
		
		/* Creates a new CommandBarControl object and adds it to the collection of controls on the specified command bar. */
		CommandBarControl Add(MsoControlType type, int controlid);
		
	};


	/* Represents a command bar control.*/
	class CommandBarControl
	{
	protected:
		IDispatch* m_pObject;

	public:
		// Constructor
		CommandBarControl();
		// Constructor
		CommandBarControl(IDispatch* pCommandBarControl, bool pAddRef = false);
		// Copy Constructor
		CommandBarControl(const CommandBarControl& copy);
		// Destructor
		~CommandBarControl();
		// Assignment operator
		CommandBarControl& operator=(const CommandBarControl& copy);
		// Cast operator
		operator IDispatch*() const;
		
		/* Returns or sets the caption text for a command bar control.*/
		std::basic_string<TCHAR> getCaption() const;
		void setCaption(const std::basic_string<TCHAR>& caption);
		/* Returns or sets the name of a procedure that will run when the user clicks or changes the value of a command bar control. */
		std::basic_string<TCHAR> getOnAction() const;
		void setOnAction(const std::basic_string<TCHAR>& onaction);
		
		
		
	};

	class CommandBarControls;

	/* Represents a pop-up control on a command bar.*/
	class CommandBarPopup
	: public CommandBarControl
	{

	public:
		// Constructor
		CommandBarPopup();
		// Constructor
		CommandBarPopup(IDispatch* pCommandBarPopup, bool pAddRef = false);
		
		/* Returns a CommandBarControls object that represents all the controls on a command bar or pop-up control. */
		CommandBarControls getControls() const;
		
		
		
	};

	class CommandBarButton;

	/* Represents a button control on a command bar.*/
	class CommandBarButton
	: public CommandBarControl
	{

	public:
		// Constructor
		CommandBarButton();
		// Constructor
		CommandBarButton(IDispatch* pCommandBarButton, bool pAddRef = false);
		
		
		
		void Click(CommandBarButton const& ctrl, bool& canceldefault);
		
		static const GUID IID_CommandBarButtonEvents;
	};


}

#endif