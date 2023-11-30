-- 创建用户表
CREATE TABLE `users` (
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
CREATE TABLE `groups` (
  `group_id` INT NOT NULL AUTO_INCREMENT,
  `group_name` VARCHAR(255) NOT NULL,
  `group_notice` VARCHAR(255) NOT NULL,
  `group_members` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`group_id`)
);

CREATE TABLE user_groups (
    user_id INT NOT NULL,
    group_id INT NOT NULL,
    PRIMARY KEY (user_id, group_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (group_id) REFERENCES `groups`(`group_id`)
);

DELIMITER //

CREATE TRIGGER before_delete_user_group
BEFORE DELETE ON user_groups
FOR EACH ROW
BEGIN
    DECLARE member_count INT;

    -- 获取当前组的成员数量
    SELECT LENGTH(group_members) - LENGTH(REPLACE(group_members, ',', '')) + 1
    INTO member_count
    FROM `groups`
    WHERE group_id = OLD.group_id;

    -- 如果成员数量大于1，说明不是最后一个成员，直接删除
    IF member_count > 1 THEN
        UPDATE `groups`
        SET group_members = REPLACE(group_members, CONCAT(',', OLD.user_id), '')
        WHERE group_id = OLD.group_id;
    ELSE
        -- 如果是最后一个成员，直接删除整个组
        DELETE FROM `groups`
        WHERE group_id = OLD.group_id;
    END IF;
END //

DELIMITER ;
