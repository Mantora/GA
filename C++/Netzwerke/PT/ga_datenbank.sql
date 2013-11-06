/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50516
Source Host           : localhost:3306
Source Database       : ga_datenbank

Target Server Type    : MYSQL
Target Server Version : 50516
File Encoding         : 65001

Date: 2013-09-05 17:45:19
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `log_cj`
-- ----------------------------
DROP TABLE IF EXISTS `log_cj`;
CREATE TABLE `log_cj` (
  `user_id` int(11) NOT NULL DEFAULT '0',
  `date` datetime DEFAULT NULL,
  `space_count` int(11) DEFAULT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of log_cj
-- ----------------------------
INSERT INTO `log_cj` VALUES ('1', '2013-09-04 17:47:04', '16');

-- ----------------------------
-- Table structure for `log_daniel`
-- ----------------------------
DROP TABLE IF EXISTS `log_daniel`;
CREATE TABLE `log_daniel` (
  `name` varchar(128) NOT NULL,
  `spacePressedCount` int(11) DEFAULT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of log_daniel
-- ----------------------------

-- ----------------------------
-- Table structure for `users`
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `ID` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Die eineindeutige ID des benutzers',
  `NAME` varchar(128) NOT NULL COMMENT 'Der Name des Benutzers',
  `PASSWORD` char(40) NOT NULL COMMENT 'das Password feld ist immer 40 Zeichen lang, da SHA(''abc'') 40 zeichen zurückgibt',
  PRIMARY KEY (`ID`),
  FULLTEXT KEY `NAME` (`NAME`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of users
-- ----------------------------
INSERT INTO `users` VALUES ('1', 'CJ', '17ba0791499db908433b80f37c5fbc89b870084b');
INSERT INTO `users` VALUES ('2', 'Daniel', 'f881b44b0c8b0ace5bc97cf6066fda86c2af6e18');
