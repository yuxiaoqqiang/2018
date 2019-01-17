TYPE=TRIGGERS
triggers='CREATE DEFINER=`zxrtt`@`%` TRIGGER `commender` AFTER INSERT ON `comments` FOR EACH ROW begin\nDECLARE c int;\nset c = (select Comment_of_people from movie where Name = new.Movie_Name);\nupdate movie set Comment_of_people = c + 1 WHERE\nName = new.Movie_Name;\nend'
sql_modes=0
definers='zxrtt@%'
client_cs_names='utf8mb4'
connection_cl_names='utf8mb4_unicode_ci'
db_cl_names='latin1_swedish_ci'
created=148345714079
