	CREATE TABLE Work (
			role VARCHAR(50)
		,
			works  INT NOT NULL ,
			FOREIGN KEY(works) REFERENCES Professor(ID)
,			is_in  VARCHAR(50) NOT NULL,
			FOREIGN KEY(is_in) REFERENCES University(Location)
	) ENGINE=InnoDB;
	SELECT * FROM Work;
	SELECT role FROM Work WHERE role = ?; 
