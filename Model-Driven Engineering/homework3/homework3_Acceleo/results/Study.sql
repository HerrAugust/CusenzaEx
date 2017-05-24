	CREATE TABLE Study (
		
			studies  INT NOT NULL ,
			FOREIGN KEY(studies) REFERENCES Professor(ID)
,			is_studied  INT NOT NULL ,
			FOREIGN KEY(is_studied) REFERENCES Subject(ID)
	) ENGINE=InnoDB;
	SELECT * FROM Study;
	 
