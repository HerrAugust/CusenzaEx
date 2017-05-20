SYNTAXDEF wap //this is the extension of our files
FOR <http://org.disim/WebApplication> 
START WebApplicationModel

OPTIONS {
	reloadGeneratorModel = "true";
}

TOKENS	{
	DEFINE	COMMENT	$'//'(~('\n'|'\r'|'\uffff'))*	$;
}

TOKENSTYLES	{
	"TEXT"	COLOR	#000000;
	"WebApplication" COLOR #da0000 , BOLD;
	"Data" COLOR #da0000 , BOLD;
	"DataSources" COLOR #da0000 , BOLD;
	"Entities" COLOR #da0000 , BOLD;
	"Entity" COLOR #da0000 , BOLD;
	"Links" COLOR #da0000 , BOLD;
	"Content" COLOR #da0000 , BOLD;
	"Relates to" COLOR #da0000 , BOLD;
	"Pages" COLOR #da0000 , BOLD;
	"Columns" COLOR #da0000 , BOLD;
	"Column" COLOR #da0000 , BOLD;
	"RelatedEntity" COLOR #da0000 , BOLD;
	"Page" COLOR #da0000 , BOLD;
	"Link" COLOR #da0000 , BOLD;
	"Forms" COLOR #da0000 , BOLD;
	"Form" COLOR #da0000 , BOLD;
	"Contents" COLOR #da0000 , BOLD;
	"MultipleContent" COLOR #da0000 , BOLD;
	"SingleContent" COLOR #da0000 , BOLD;
	"Menu" COLOR #da0000 , BOLD;
	"COMMENT"	COLOR	#00bb00	,	ITALIC	;
}

RULES {
	// syntax definition for class 'StartMetaClass'
	WebApplicationModel ::= 
	"WebApplication" "{"
		("name=" name[] ",")?
		"Data" "{"
			"DataSources" "{"
				dataSources*
			"},"
			"Entities" "{"
				entities* 
			"}"
		"}," 
		"Content" "{"
			"Pages" "{"
				pages*
			"}"
		"}"
	"}";
	
	//data sources
	Data.DataSource ::= name[]? "for" "Entity" entity[];
	
	//entities
	Data.Entity   ::=
		"Entity" ("name=" name[])? "{"
			"Columns" "{"
				columns+
			"}"
			"Relates to" "{"
				relates*
			"}"
		"}";
	
	Data.Column ::= "Column" "{" ("name=" name[])? ("length=" lenght[])? ("isPK=" PK[])? "type=" type[] "}";
		
	Data.RelatedEntity ::= "RelatedEntity" "{" ("name=" name[])? "RelatedEntity=" relatesTo[] "}";
	
	//pages
	Content.Page ::=
		"Page" "{"
			("name=" name[])?
			"Links" "{"
				links*
			"},"
			"Forms" "{"
				forms*
			"},"
			"Contents" "{"
				contents*
			"}"
		"}";
	
	Content.Link ::= "Link" "{" ("name=" name['"','"'])? "from" from[] "to" to[] "}";
	
	Content.CRUDForm ::= "Form" "{" ("name=" name[])? "Fields" "{" fields* "}" "}";
	
	Content.Field ::= "Field" "{" ("name=" name[])? ("type=" type[])? "}";
	
	//Content.Content is abstract => not defined here
	
	Content.Menu ::= "Menu" "{" ("name=" name['"','"'])? ("itemName=" itemName['"','"'])? ("url=" url['"','"'])? ("order=" order[])? "dataSource=" dataSource[] "}";
	
	Content.SingleContent ::= "SingleContent" "{" ("name=" name['"','"'])? "dataSource=" dataSource[] "}";
	
	Content.MultipleContent ::= "MultipleContent" "{" ("name=" name['"','"'])? ("paginated=" paginated[])? ("size=" size[])? "dataSource=" dataSource[] "}";
	
	Content.Form ::= "name=" name[]?;
	
	//Added to suppress Eclipse warning
	Named ::= "name=" name['"','"']?;
	
	//12 definitions (except Form and Named). classes are 15 - 1 abstract - 2 superclasses = 12 metaclasses => 0K.
}