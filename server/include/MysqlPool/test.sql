CREATE DATABASE chat_online;
use chat_online;


-- 创建用户表
CREATE TABLE `user` (
  `user_id` INT NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(255) NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `email` VARCHAR(255) NOT NULL,
  `phone` VARCHAR(11) NOT NULL,
  `avatar` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`user_id`)
);

-- 创建聊天记录表
CREATE TABLE `chat_record` (
  `chat_record_id` INT NOT NULL AUTO_INCREMENT,
  `sender_id` INT NOT NULL,
  `receiver_id` INT NOT NULL,
  `chat_content` VARCHAR(255) NOT NULL,
  `chat_time` DATETIME NOT NULL,
  PRIMARY KEY (`chat_record_id`)
);

-- 创建群组表
CREATE TABLE `group` (
  `group_id` INT NOT NULL AUTO_INCREMENT,
  `group_name` VARCHAR(255) NOT NULL,
  `group_notice` VARCHAR(255) NOT NULL,
  `group_members` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`group_id`)
);
