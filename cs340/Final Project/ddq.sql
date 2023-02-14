-- MySQL dump 10.16  Distrib 10.1.37-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: bsg
-- ------------------------------------------------------
-- Server version	10.1.37-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table 'Accounts'
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Accounts` (
  `Account_id` int(11) NOT NULL AUTO_INCREMENT,
  `Username` varchar(15) NOT NULL,
  `Email` varchar(255) NOT NULL,
  PRIMARY KEY (`Account_id`)
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table 'Accounts'
--

LOCK TABLES `Accounts` WRITE;
/*!40000 ALTER TABLE `Accounts` DISABLE KEYS */;
INSERT INTO `Accounts` VALUES 
(1,'footballguy12', 'jeffk@hello.com'),
(2,'albthatsme', 'aliceb@hello.com'),
(3,'roberth77', 'bobh@hello.com'),
(4,'ashleyf98', 'ashleyf@hello.com');
/*!40000 ALTER TABLE `Accounts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table 'Posts'
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Posts` (
  `Post_id` int(11) NOT NULL AUTO_INCREMENT,
  `Text` varchar(255) NOT NULL,
  `Account_id` int(11) NOT NULL,
  `Timestamp` datetime NOT NULL,
  FOREIGN KEY (`Account_id`) REFERENCES Accounts (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`Post_id`)
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table 'Post_id'
--

LOCK TABLES `Posts` WRITE;
/*!40000 ALTER TABLE `Posts` DISABLE KEYS */;
INSERT INTO `Posts` VALUES
(1, 'This is my first post!', 1, '2012-04-10 07:26:38'),
(2, 'Hello World!', 2, '2012-04-15 08:26:00'),
(3, 'Welcome!', 3, '2012-04-11 07:16:57'),
(4, 'Hello everyone!', 4, '2012-04-11 07:30:57');
/*!40000 ALTER TABLE `Posts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Comments`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Comments` (
  `Comment_id` int(11) NOT NULL AUTO_INCREMENT,
  `Text` varchar(280) NOT NULL,
  `Account_id` int(11) NOT NULL,
  `Post_id` int(11) NOT NULL,
  `Timestamp` datetime NOT NULL,
  PRIMARY KEY (`Comment_id`),
  FOREIGN KEY (`Account_id`) REFERENCES `Accounts` (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`Post_id`) REFERENCES `Posts` (`Post_id`) ON DELETE CASCADE ON UPDATE CASCADE
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Comments`
--

LOCK TABLES `Comments` WRITE;
/*!40000 ALTER TABLE `Comments` DISABLE KEYS */;
INSERT INTO `Comments` VALUES 
(1,'Nice post!', 2, 3, '2012-05-03 12:46:59'),
(2,'Yeah I agree.', 1, 2, '2012-05-04 12:02:59'),
(3,'lol',4, 1, '2012-05-03 06:17:03'),
(4,'yeah true I think',4, 3, '2012-05-02 17:32:10'),
(5,'what do you mean?',3, 4, '2012-05-02 18:02:03'),
(6,'love this.',2, 2, '2012-05-03 13:39:56');
/*!40000 ALTER TABLE `Comments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table 'Groups'
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Groups` (
  `Group_id` int(11) NOT NULL AUTO_INCREMENT,
  `Group_name` varchar(255) NOT NULL,
  PRIMARY KEY (`Group_id`)
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Groups`
--

LOCK TABLES `Groups` WRITE;
/*!40000 ALTER TABLE `Groups` DISABLE KEYS */;
INSERT INTO `Groups` VALUES
(1, 'Group 1'),
(2, 'Group 2');
/*!40000 ALTER TABLE `Groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Memberships`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Memberships` (
  `Account_id` int(11) NOT NULL,
  `Group_id` int(11) NOT NULL,
  FOREIGN KEY (`Account_id`) REFERENCES Accounts (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`Group_id`) REFERENCES Groups (`Group_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`Account_id`, `Group_id`)
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Memberships`
--

LOCK TABLES `Memberships` WRITE;
/*!40000 ALTER TABLE `Memberships` DISABLE KEYS */;
INSERT INTO `Memberships` VALUES
(1, 1),
(2, 1),
(3, 2),
(3, 1),
(4, 2);
/*!40000 ALTER TABLE `Memberships` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Messages`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Messages` (
  `Message_id` int(11) NOT NULL AUTO_INCREMENT,
  `Account_id` int(11) NOT NULL,
  `Group_id` int(11) NOT NULL,
  `Message` varchar(255) NOT NULL,
  `Timestamp` datetime NOT NULL,
  FOREIGN KEY (`Account_id`) REFERENCES Accounts (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`Group_id`) REFERENCES Groups (`Group_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`Message_id`)
) ;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Messages`
--

LOCK TABLES `Messages` WRITE;
/*!40000 ALTER TABLE `Messages` DISABLE KEYS */;
INSERT INTO `Messages` VALUES
(1, 1, 1, 'Hello', '2012-05-04 14:39:56'),
(2, 2, 1, 'Whats up', '2012-05-04 14:40:56'),
(3, 3, 2, 'I like this group better', '2012-05-04 14:41:56'),
(4, 4, 2, 'Interesting', '2012-05-04 14:42:04'),
(5, 3, 2, 'How are you doing?', '2012-05-04 14:42:40'),
(6, 4, 2, 'Great!', '2012-05-04 14:43:17');
/*!40000 ALTER TABLE `Messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Friendships`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Friendships` (
  `From_Account_id` int(11) NOT NULL,
  `To_Account_id` int(11) NOT NULL,
  FOREIGN KEY (`From_Account_id`) REFERENCES Accounts (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`To_Account_id`) REFERENCES Accounts (`Account_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`From_Account_id`, `To_Account_id`)
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Friendships`
--

LOCK TABLES `Friendships` WRITE;
/*!40000 ALTER TABLE `Friendships` DISABLE KEYS */;
INSERT INTO `Friendships` VALUES 
(1, 2),
(1, 3),
(4, 2),
(2, 3),
(3, 1),
(4, 1);
/*!40000 ALTER TABLE `Friendships` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
