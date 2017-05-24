	CREATE TABLE Professor (
			ID INT NOT NULL AUTO_INCREMENT
,			Name VARCHAR(50)
,			researchFieldID INT 
		,
			research  INT NOT NULL ,
			FOREIGN KEY(research) REFERENCES ResearchField(ID)
	) ENGINE=InnoDB;
	SELECT * FROM Professor;
	SELECT Name,researchFieldID FROM Professor WHERE ID = ?; 
