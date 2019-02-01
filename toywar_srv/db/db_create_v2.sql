SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `toywar_v2` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;
USE `toywar_v2` ;

-- -----------------------------------------------------
-- Table `toywar_v2`.`alliance`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`alliance` (
  `alliance_id` INT UNSIGNED NOT NULL ,
  `name` VARCHAR(50) NULL ,
  `flag` TINYINT NULL ,
  `leader_uid` INT UNSIGNED NOT NULL ,
  `create_time` INT UNSIGNED NULL ,
  `status` TINYINT NULL ,
  `level` TINYINT NULL ,
  `point` BIGINT NULL ,
  `rank` INT NULL ,
  `member_count` TINYINT UNSIGNED NULL ,
  `enemy_alliance_id` INT UNSIGNED NULL ,
  `enemy_alliance_name` VARCHAR(50) NULL ,
  `description` VARCHAR(200) NULL ,
  `notice` VARCHAR(200) NULL ,
  `activity` VARCHAR(2000) NULL ,
  `extra_data` VARCHAR(2000) NULL ,
  PRIMARY KEY (`alliance_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user` (
  `uid` INT UNSIGNED NOT NULL ,
  `register_platform` TINYINT NULL ,
  `register_time` INT UNSIGNED NULL ,
  `invite_uid` INT UNSIGNED NOT NULL ,
  `last_login_platform` TINYINT NULL ,
  `last_login_time` INT UNSIGNED NULL ,
  `last_active_time` INT UNSIGNED NULL ,
  `login_times` INT UNSIGNED NULL ,
  `invite_count` INT UNSIGNED NULL ,
  `status` TINYINT NULL ,
  `main_base_id` INT UNSIGNED NOT NULL ,
  `level` TINYINT UNSIGNED NULL ,
  `point` BIGINT UNSIGNED NULL ,
  `value` BIGINT UNSIGNED NULL ,
  `tutorial_stage` SMALLINT NULL ,
  `r1` INT UNSIGNED NULL ,
  `r1_max` INT UNSIGNED NULL ,
  `r2` INT UNSIGNED NULL ,
  `r2_max` INT UNSIGNED NULL ,
  `r3` INT UNSIGNED NULL ,
  `r3_max` INT UNSIGNED NULL ,
  `r4` INT UNSIGNED NULL ,
  `r4_max` INT UNSIGNED NULL ,
  `alliance_id` INT UNSIGNED NOT NULL ,
  `unread_message` SMALLINT UNSIGNED NULL ,
  `gift_send` SMALLINT UNSIGNED NULL ,
  `gate_left_times` SMALLINT UNSIGNED NULL ,
  `gate_extra_times` SMALLINT UNSIGNED NULL ,
  `user_stat` VARCHAR(500) NULL ,
  `user_flag` VARCHAR(500) NULL ,
  `wf_status` VARCHAR(500) NULL ,
  PRIMARY KEY (`uid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_mapping`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_mapping` (
  `open_id` VARCHAR(64) NOT NULL ,
  `platform` TINYINT NOT NULL ,
  `uid` INT UNSIGNED NOT NULL ,
  `updatetime` INT NULL ,
  PRIMARY KEY (`open_id`, `platform`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`base`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`base` (
  `baseid` INT UNSIGNED NOT NULL ,
  `uid` INT UNSIGNED NOT NULL ,
  `base_index` INT NULL ,
  `type` TINYINT NULL ,
  `base_name` VARCHAR(50) NULL ,
  `seed` SMALLINT UNSIGNED NULL ,
  `x` INT NULL ,
  `y` INT NULL ,
  `create_time` INT UNSIGNED NULL ,
  `save_time` INT UNSIGNED NULL ,
  `saveby_uid` INT UNSIGNED NOT NULL ,
  `protected_time` INT UNSIGNED NULL ,
  `last_active_time` INT NULL ,
  `status` TINYINT NULL ,
  `damage` TINYINT NULL ,
  `destroyed` TINYINT NULL ,
  `value` BIGINT UNSIGNED NULL ,
  `last_mashroom_time` INT UNSIGNED NULL ,
  `last_update_id` INT UNSIGNED NULL ,
  `updates` VARCHAR(3000) NULL ,
  `effect` TEXT NULL ,
  `aiattack` VARCHAR(500) NULL ,
  `manoeuvre` VARCHAR(500) NULL ,
  PRIMARY KEY (`baseid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`building`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`building` (
  `baseid` INT UNSIGNED NOT NULL ,
  `building_id` INT UNSIGNED NOT NULL ,
  `type` INT UNSIGNED NOT NULL ,
  `x` SMALLINT NULL ,
  `y` SMALLINT NULL ,
  `level` TINYINT UNSIGNED NULL ,
  `production` VARCHAR(20) NULL ,
  `status` INT NULL ,
  `hp` INT NULL ,
  `build_count` INT NULL ,
  `upgrade_count` INT NULL ,
  `repair_count` INT NULL ,
  `update_time` INT NULL ,
  `production_stage` INT NULL ,
  `production_count` INT NULL ,
  `help_list` VARCHAR(45) NULL ,
  `create_time` INT NULL ,
  PRIMARY KEY (`baseid`, `building_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`technology`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`technology` (
  `uid` INT UNSIGNED NOT NULL ,
  `toy_type` CHAR(8) NOT NULL ,
  `level` TINYINT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `toy_type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`toy`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`toy` (
  `baseid` INT UNSIGNED NOT NULL ,
  `type` CHAR(8) NOT NULL ,
  `count` INT UNSIGNED NULL ,
  PRIMARY KEY (`baseid`, `type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`pay`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`pay` (
  `uid` INT UNSIGNED NOT NULL ,
  `cash` INT UNSIGNED NOT NULL ,
  PRIMARY KEY (`uid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`attack`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`attack` (
  `attack_id` BIGINT UNSIGNED NOT NULL ,
  `attack_uid` INT UNSIGNED NOT NULL ,
  `defence_uid` INT UNSIGNED NOT NULL ,
  `defence_baseid` INT UNSIGNED NOT NULL ,
  `attack_platform` TINYINT NULL ,
  `attack_user_name` VARCHAR(32) NULL ,
  `attack_photo` VARCHAR(300) NULL ,
  `attack_alliance_id` INT UNSIGNED NOT NULL ,
  `attack_alliance_name` VARCHAR(50) NULL ,
  `attack_alliance_flag` TINYINT NULL ,
  `defence_platform` TINYINT NULL ,
  `defence_user_name` VARCHAR(32) NULL ,
  `defence_photo` VARCHAR(300) NULL ,
  `defence_base_name` VARCHAR(50) NULL ,
  `defence_alliance_id` INT UNSIGNED NOT NULL ,
  `defence_alliance_name` VARCHAR(50) NULL ,
  `defence_alliance_flag` TINYINT NULL ,
  `start_time` INT UNSIGNED NULL ,
  `end_time` INT UNSIGNED NULL ,
  `r1_loot` INT NULL ,
  `r2_loot` INT NULL ,
  `r3_loot` INT NULL ,
  `r4_loot` INT NULL ,
  `log` TEXT NULL ,
  PRIMARY KEY (`attack_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`quest`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`quest` (
  `uid` INT UNSIGNED NOT NULL ,
  `questid` CHAR(8) NOT NULL ,
  `state` TINYINT NULL ,
  PRIMARY KEY (`uid`, `questid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`consume`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`consume` (
  `uid` INT UNSIGNED NOT NULL ,
  `baseid` INT UNSIGNED NOT NULL ,
  `type` VARCHAR(16) NOT NULL ,
  `count` INT UNSIGNED NULL ,
  `end_time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `baseid`, `type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_attack`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_attack` (
  `uid` INT UNSIGNED NOT NULL ,
  `attack_id` BIGINT UNSIGNED NOT NULL ,
  `opposite_uid` INT UNSIGNED NOT NULL ,
  `opposite_platform` TINYINT NULL ,
  `defence_baseid` INT UNSIGNED NULL ,
  `type` TINYINT NULL ,
  `status` TINYINT NULL ,
  `start_time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `attack_id`) ,
  INDEX `idx_time` (`uid` ASC, `start_time` ASC, `type` ASC, `defence_baseid` ASC) ,
  INDEX `idx_status` (`uid` ASC, `status` ASC, `type` ASC, `defence_baseid` ASC, `start_time` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`cash_flow`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`cash_flow` (
  `uid` INT UNSIGNED NOT NULL ,
  `flow_id` BIGINT UNSIGNED NOT NULL ,
  `type` VARCHAR(16) NULL ,
  `count` INT NULL ,
  `cash` INT NULL ,
  `balance` INT UNSIGNED NULL ,
  `time` INT UNSIGNED NULL ,
  `data` INT UNSIGNED NULL ,
  PRIMARY KEY (`flow_id`) ,
  INDEX `idx_user_time_type` (`uid` ASC, `time` DESC, `type` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`produce_line`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`produce_line` (
  `baseid` INT UNSIGNED NOT NULL ,
  `building_id` INT UNSIGNED NOT NULL ,
  `line_id` TINYINT UNSIGNED NOT NULL ,
  `type` CHAR(8) NULL ,
  `count` TINYINT UNSIGNED NULL ,
  PRIMARY KEY (`baseid`, `building_id`, `line_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_base`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_base` (
  `uid` INT UNSIGNED NOT NULL ,
  `base_index` INT NOT NULL ,
  `baseid` INT UNSIGNED NOT NULL ,
  PRIMARY KEY (`uid`, `base_index`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`pay_history`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`pay_history` (
  `uid` INT UNSIGNED NOT NULL ,
  `pay_id` BIGINT UNSIGNED NOT NULL ,
  `type` SMALLINT NULL ,
  `channel` TINYINT NULL ,
  `channel_pay_id` VARCHAR(64) NULL ,
  `credit` INT NULL ,
  `count` INT NULL ,
  `status` TINYINT NULL ,
  `time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `pay_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`recycle`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`recycle` (
  `baseid` INT UNSIGNED NOT NULL ,
  `type` CHAR(16) NOT NULL ,
  `count` INT NULL ,
  PRIMARY KEY (`baseid`, `type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`research`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`research` (
  `uid` INT UNSIGNED NOT NULL ,
  `toy_type` CHAR(8) NOT NULL ,
  `research_type` TINYINT NOT NULL ,
  `start_time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `toy_type`, `research_type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_interact`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_interact` (
  `uid` INT UNSIGNED NOT NULL ,
  `opposite_uid` INT UNSIGNED NOT NULL ,
  `help_from` SMALLINT UNSIGNED NULL ,
  `help_to` SMALLINT UNSIGNED NULL ,
  `attack_from` SMALLINT UNSIGNED NULL ,
  `attack_to` SMALLINT UNSIGNED NULL ,
  `retaliate_count` SMALLINT UNSIGNED NULL ,
  `last_attack_time` INT UNSIGNED NULL ,
  `truce_time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `opposite_uid`) ,
  INDEX `idx_attack_time` (`uid` ASC, `last_attack_time` DESC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_basic`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_basic` (
  `uid` INT UNSIGNED NOT NULL ,
  `platform` TINYINT NOT NULL ,
  `is_register_platform` TINYINT NULL ,
  `open_id` VARCHAR(64) NOT NULL ,
  `name` VARCHAR(32) NULL ,
  `gender` TINYINT NULL ,
  `nation` VARCHAR(32) NULL ,
  `province` VARCHAR(32) NULL ,
  `city` VARCHAR(32) NULL ,
  `figure_url` VARCHAR(300) NULL ,
  `vip_type` TINYINT NULL ,
  `vip_level` TINYINT NULL ,
  `friends` VARCHAR(5000) NULL ,
  PRIMARY KEY (`uid`, `platform`) ,
  INDEX `idx_user_platform` (`uid` ASC, `platform` ASC) ,
  INDEX `idx_user_register` (`uid` ASC, `is_register_platform` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`temp_base`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`temp_base` (
  `baseid` INT UNSIGNED NOT NULL ,
  `data` TEXT NULL ,
  PRIMARY KEY (`baseid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`neighbour`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`neighbour` (
  `uid` INT UNSIGNED NOT NULL ,
  `neighbours` VARCHAR(2000) NULL ,
  PRIMARY KEY (`uid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`gate`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`gate` (
  `uid` INT UNSIGNED NOT NULL ,
  `level` SMALLINT NOT NULL ,
  `is_win` TINYINT NULL ,
  `dare_times` SMALLINT NULL ,
  `win_score` SMALLINT NULL ,
  `lose_score` SMALLINT NULL ,
  `best_score` SMALLINT NULL ,
  `use_time` SMALLINT NULL ,
  `use_resource` INT NULL ,
  `last_save_time` INT UNSIGNED NULL DEFAULT 0 ,
  `status` TINYINT NULL DEFAULT 0 ,
  PRIMARY KEY (`uid`, `level`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`id_ctrl`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`id_ctrl` (
  `id_key` TINYINT NOT NULL ,
  `curr_id` BIGINT UNSIGNED NULL ,
  PRIMARY KEY (`id_key`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`message`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`message` (
  `message_id` BIGINT UNSIGNED NOT NULL ,
  `from_uid` INT UNSIGNED NOT NULL ,
  `to_uid` INT UNSIGNED NOT NULL ,
  `from_platform` TINYINT NULL ,
  `from_user_name` VARCHAR(32) NULL ,
  `from_photo` VARCHAR(300) NULL ,
  `to_platform` TINYINT NULL ,
  `to_user_name` VARCHAR(32) NULL ,
  `to_photo` VARCHAR(300) NULL ,
  `time` INT UNSIGNED NULL ,
  `type` TINYINT NULL ,
  `status` TINYINT NOT NULL ,
  `content` VARCHAR(200) NULL ,
  `reply_id` BIGINT UNSIGNED NOT NULL ,
  PRIMARY KEY (`message_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_message`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_message` (
  `uid` INT UNSIGNED NOT NULL ,
  `message_id` BIGINT UNSIGNED NOT NULL ,
  `opposite_uid` INT UNSIGNED NOT NULL ,
  `toward` TINYINT NULL ,
  `type` TINYINT NULL ,
  `status` TINYINT NULL ,
  `time` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `message_id`) ,
  INDEX `idx_time` (`uid` ASC, `time` DESC, `type` ASC, `toward` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`alliance_member`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`alliance_member` (
  `alliance_id` INT UNSIGNED NOT NULL ,
  `uid` INT UNSIGNED NOT NULL ,
  `type` TINYINT NULL ,
  `point` BIGINT NULL ,
  `join_time` INT UNSIGNED NULL ,
  `extra_data` VARCHAR(2000) NULL ,
  PRIMARY KEY (`alliance_id`, `uid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`alliance_mapping`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`alliance_mapping` (
  `alliance_name` VARCHAR(50) NOT NULL ,
  `alliance_id` INT UNSIGNED NOT NULL ,
  PRIMARY KEY (`alliance_name`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`user_data`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`user_data` (
  `uid` INT UNSIGNED NOT NULL ,
  `data` TEXT NULL ,
  PRIMARY KEY (`uid`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`inventory`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`inventory` (
  `uid` INT UNSIGNED NOT NULL ,
  `type` VARCHAR(16) NOT NULL ,
  `count` INT UNSIGNED NULL ,
  PRIMARY KEY (`uid`, `type`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `toywar_v2`.`platform_user`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `toywar_v2`.`platform_user` (
  `open_id` VARCHAR(64) NOT NULL ,
  `platform` TINYINT NOT NULL ,
  `data` TEXT NULL ,
  PRIMARY KEY (`open_id`, `platform`) )
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `toywar_v2`.`user`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
USE `toywar_v2`;
INSERT INTO `toywar_v2`.`user` (`uid`, `register_platform`, `register_time`, `invite_uid`, `last_login_platform`, `last_login_time`, `last_active_time`, `login_times`, `invite_count`, `status`, `main_base_id`, `level`, `point`, `value`, `tutorial_stage`, `r1`, `r1_max`, `r2`, `r2_max`, `r3`, `r3_max`, `r4`, `r4_max`, `alliance_id`, `unread_message`, `gift_send`, `gate_left_times`, `gate_extra_times`, `user_stat`, `user_flag`, `wf_status`) VALUES ('10000000', NULL, NULL, '10000000', NULL, NULL, NULL, NULL, NULL, NULL, '10000000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '0', NULL, NULL, NULL, NULL, NULL, NULL, NULL);

COMMIT;

-- -----------------------------------------------------
-- Data for table `toywar_v2`.`base`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
USE `toywar_v2`;
INSERT INTO `toywar_v2`.`base` (`baseid`, `uid`, `base_index`, `type`, `base_name`, `seed`, `x`, `y`, `create_time`, `save_time`, `saveby_uid`, `protected_time`, `last_active_time`, `status`, `damage`, `destroyed`, `value`, `last_mashroom_time`, `last_update_id`, `updates`, `effect`, `aiattack`, `manoeuvre`) VALUES ('10000000', '10000000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '10000000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

COMMIT;

-- -----------------------------------------------------
-- Data for table `toywar_v2`.`id_ctrl`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
USE `toywar_v2`;
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('1', '10000000');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('20', '10000000');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('40', '0');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('50', '0');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('61', '0');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('62', '0');
INSERT INTO `toywar_v2`.`id_ctrl` (`id_key`, `curr_id`) VALUES ('70', '4010000000');

COMMIT;
