	CREATE TABLE ResearchField (
			ID INT NOT NULL AUTO_INCREMENT
,			Name VARCHAR(50)
		
			,PRIMARY KEY(ID)
	) ENGINE=InnoDB;
	SELECT * FROM ResearchField;
	SELECT Name FROM ResearchField WHERE ID = ?; 
