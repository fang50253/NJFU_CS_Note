-- MySQL dump 10.13  Distrib 8.0.43, for Win64 (x86_64)
--
-- Host: localhost    Database: testdb
-- ------------------------------------------------------
-- Server version	8.4.6

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `book` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `title` varchar(200) NOT NULL,
  `author` varchar(100) NOT NULL,
  `isbn` varchar(20) DEFAULT NULL,
  `price` decimal(10,2) DEFAULT NULL,
  `category` varchar(50) DEFAULT NULL,
  `publisher` varchar(100) DEFAULT NULL,
  `publish_date` date DEFAULT NULL,
  `stock_quantity` int DEFAULT '0',
  `status` tinyint DEFAULT '1' COMMENT '1:可用, 0:不可用',
  `create_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `update_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `isbn` (`isbn`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES (1,'Java编程思想','Bruce Eckel','9787111213826',88.00,'编程','机械工业出版社','2007-06-01',45,1,'2025-11-17 03:27:45','2025-11-17 03:43:37'),(2,'Spring实战','Craig Walls','9787115528322',88.00,'编程','人民邮电出版社','2020-01-01',30,1,'2025-11-17 03:27:45','2025-11-17 03:43:37'),(3,'MyBatis从入门到精通','刘增辉','9787121346235',88.00,'编程','电子工业出版社','2018-07-01',25,1,'2025-11-17 03:27:45','2025-11-17 03:43:37'),(4,'数据库系统概念','Abraham Silberschatz','9787111615421',99.00,'数据库','机械工业出版社','2019-03-01',20,1,'2025-11-17 03:27:45','2025-11-17 03:27:45'),(5,'算法导论','Thomas H. Cormen','9787111407010',128.00,'算法','机械工业出版社','2012-12-01',15,1,'2025-11-17 03:27:45','2025-11-17 03:27:45');
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-11-17 11:48:52
