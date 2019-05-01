package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Base extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REGISTER_PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.register_platform", "registerPlatform", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var registerPlatform:uint;

		/**
		 *  @private
		 */
		public static const REGISTER_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.register_time", "registerTime", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var registerTime:uint;

		/**
		 *  @private
		 */
		public static const INVITE_UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.invite_uid", "inviteUid", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var inviteUid:uint;

		/**
		 *  @private
		 */
		public static const LAST_LOGIN_PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_login_platform", "lastLoginPlatform", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastLoginPlatform:uint;

		/**
		 *  @private
		 */
		public static const LAST_LOGIN_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_login_time", "lastLoginTime", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastLoginTime:uint;

		/**
		 *  @private
		 */
		public static const LOGIN_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.login_times", "loginTimes", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loginTimes:uint;

		/**
		 *  @private
		 */
		public static const LOGIN_DAYS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.login_days", "loginDays", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loginDays:uint;

		/**
		 *  @private
		 */
		public static const LAST_ACTIVE_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_active_time", "lastActiveTime", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastActiveTime:uint;

		/**
		 *  @private
		 */
		public static const LAST_OFF_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_off_time", "lastOffTime", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastOffTime:uint;

		/**
		 *  @private
		 */
		public static const FORBID_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.forbid_ts", "forbidTs", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var forbidTs:uint;

		/**
		 *  @private
		 */
		public static const FORBID_REASON:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.forbid_reason", "forbidReason", (11 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var forbidReason:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const INVITE_COUNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.invite_count", "inviteCount", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var inviteCount:uint;

		/**
		 *  @private
		 */
		public static const TODAY_INVITE_COUNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.today_invite_count", "todayInviteCount", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		public var todayInviteCount:uint;

		/**
		 *  @private
		 */
		public static const TUTORIAL_STAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.tutorial_stage", "tutorialStage", (14 << 3) | com.netease.protobuf.WireType.VARINT);

		public var tutorialStage:uint;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.name", "name", (15 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const FIG:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.fig", "fig", (16 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var fig:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const KINGDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.kingdom", "kingdom", (17 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kingdom:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("User.Base.exp", "exp", (18 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.level", "level", (19 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const ACCCHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.acccharge", "acccharge", (20 << 3) | com.netease.protobuf.WireType.VARINT);

		public var acccharge:uint;

		/**
		 *  @private
		 */
		public static const VIPLEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.viplevel", "viplevel", (21 << 3) | com.netease.protobuf.WireType.VARINT);

		public var viplevel:uint;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.cash", "cash", (22 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.coin", "coin", (23 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.wood", "wood", (24 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wood:uint;

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.food", "food", (25 << 3) | com.netease.protobuf.WireType.VARINT);

		public var food:uint;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.iron", "iron", (26 << 3) | com.netease.protobuf.WireType.VARINT);

		public var iron:uint;

		/**
		 *  @private
		 */
		public static const TICKET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.ticket", "ticket", (27 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ticket:uint;

		/**
		 *  @private
		 */
		public static const SILK:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.silk", "silk", (28 << 3) | com.netease.protobuf.WireType.VARINT);

		public var silk:uint;

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.order", "order", (29 << 3) | com.netease.protobuf.WireType.VARINT);

		public var order:uint;

		/**
		 *  @private
		 */
		public static const BAG:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.bag", "bag", (30 << 3) | com.netease.protobuf.WireType.VARINT);

		public var bag:uint;

		/**
		 *  @private
		 */
		public static const PREWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.preward", "preward", (31 << 3) | com.netease.protobuf.WireType.VARINT);

		public var preward:uint;

		/**
		 *  @private
		 */
		public static const LOYAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.loyal", "loyal", (32 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loyal:uint;

		/**
		 *  @private
		 */
		public static const SACRIFICE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.sacrifice", "sacrifice", (33 << 3) | com.netease.protobuf.WireType.VARINT);

		public var sacrifice:uint;

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.market", "market", (34 << 3) | com.netease.protobuf.WireType.VARINT);

		public var market:uint;

		/**
		 *  @private
		 */
		public static const BMARKETCD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.bmarketcd", "bmarketcd", (35 << 3) | com.netease.protobuf.WireType.VARINT);

		public var bmarketcd:uint;

		/**
		 *  @private
		 */
		public static const BANQUET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.banquet", "banquet", (36 << 3) | com.netease.protobuf.WireType.VARINT);

		public var banquet:uint;

		/**
		 *  @private
		 */
		public static const ESHOPINTIMACY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.eshopintimacy", "eshopintimacy", (37 << 3) | com.netease.protobuf.WireType.VARINT);

		public var eshopintimacy:uint;

		/**
		 *  @private
		 */
		public static const ESHOPCD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.eshopcd", "eshopcd", (38 << 3) | com.netease.protobuf.WireType.VARINT);

		public var eshopcd:uint;

		/**
		 *  @private
		 */
		public static const REFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.refresh", "refresh", (39 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refresh:uint;

		/**
		 *  @private
		 */
		public static const AREFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.arefresh", "arefresh", (40 << 3) | com.netease.protobuf.WireType.VARINT);

		public var arefresh:uint;

		/**
		 *  @private
		 */
		public static const HARMMER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.harmmer", "harmmer", (41 << 3) | com.netease.protobuf.WireType.VARINT);

		public var harmmer:uint;

		/**
		 *  @private
		 */
		public static const SHADOW:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.shadow", "shadow", (42 << 3) | com.netease.protobuf.WireType.VARINT);

		public var shadow:uint;

		/**
		 *  @private
		 */
		public static const UP_RES_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.up_res_time", "upResTime", (43 << 3) | com.netease.protobuf.WireType.VARINT);

		public var upResTime:uint;

		/**
		 *  @private
		 */
		public static const RESTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.rests", "rests", (44 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rests:uint;

		/**
		 *  @private
		 */
		public static const MP1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mp1", "mp1", (45 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp1:uint;

		/**
		 *  @private
		 */
		public static const MP2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mp2", "mp2", (46 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp2:uint;

		/**
		 *  @private
		 */
		public static const MK1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mk1", "mk1", (47 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mk1:uint;

		/**
		 *  @private
		 */
		public static const MK2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mk2", "mk2", (48 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mk2:uint;

		/**
		 *  @private
		 */
		public static const REWARDB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.rewardb", "rewardb", (49 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardb:uint;

		/**
		 *  @private
		 */
		public static const MP3:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mp3", "mp3", (50 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp3:uint;

		/**
		 *  @private
		 */
		public static const NPC_PASS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.npc_pass", "npcPass", (51 << 3) | com.netease.protobuf.WireType.VARINT);

		public var npcPass:uint;

		/**
		 *  @private
		 */
		public static const FLAMEN_COINS_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.flamen_coins_cnt", "flamenCoinsCnt", (52 << 3) | com.netease.protobuf.WireType.VARINT);

		public var flamenCoinsCnt:uint;

		/**
		 *  @private
		 */
		public static const FLAMEM_WOOD_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.flamem_wood_cnt", "flamemWoodCnt", (53 << 3) | com.netease.protobuf.WireType.VARINT);

		public var flamemWoodCnt:uint;

		/**
		 *  @private
		 */
		public static const FLAMEM_FOOD_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.flamem_food_cnt", "flamemFoodCnt", (54 << 3) | com.netease.protobuf.WireType.VARINT);

		public var flamemFoodCnt:uint;

		/**
		 *  @private
		 */
		public static const FLAMEM_IRON_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.flamem_iron_cnt", "flamemIronCnt", (55 << 3) | com.netease.protobuf.WireType.VARINT);

		public var flamemIronCnt:uint;

		/**
		 *  @private
		 */
		public static const FIRST_RECHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.first_recharge", "firstRecharge", (56 << 3) | com.netease.protobuf.WireType.VARINT);

		public var firstRecharge:uint;

		/**
		 *  @private
		 */
		public static const AUTO_BUILD_FLAG:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.auto_build_flag", "autoBuildFlag", (57 << 3) | com.netease.protobuf.WireType.VARINT);

		public var autoBuildFlag:uint;

		/**
		 *  @private
		 */
		public static const INTEGRAL_TIME_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.integral_time_cnt", "integralTimeCnt", (58 << 3) | com.netease.protobuf.WireType.VARINT);

		public var integralTimeCnt:uint;

		/**
		 *  @private
		 */
		public static const MISSION_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mission_time", "missionTime", (59 << 3) | com.netease.protobuf.WireType.VARINT);

		public var missionTime:uint;

		/**
		 *  @private
		 */
		public static const MISSION_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.mission_id", "missionId", (60 << 3) | com.netease.protobuf.WireType.VARINT);

		public var missionId:uint;

		/**
		 *  @private
		 */
		public static const VIP_REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.vip_reward", "vipReward", (61 << 3) | com.netease.protobuf.WireType.VARINT);

		public var vipReward:uint;

		/**
		 *  @private
		 */
		public static const LADDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.ladder", "ladder", (62 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ladder:uint;

		/**
		 *  @private
		 */
		public static const LADDER_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.ladder_ts", "ladderTs", (63 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ladderTs:uint;

		/**
		 *  @private
		 */
		public static const JOB_REWARD_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.job_reward_ts", "jobRewardTs", (64 << 3) | com.netease.protobuf.WireType.VARINT);

		public var jobRewardTs:uint;

		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.department", "department", (65 << 3) | com.netease.protobuf.WireType.VARINT);

		public var department:uint;

		/**
		 *  @private
		 */
		public static const OFFICIAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.official", "official", (66 << 3) | com.netease.protobuf.WireType.VARINT);

		public var official:uint;

		/**
		 *  @private
		 */
		public static const PRESTIGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.prestige", "prestige", (67 << 3) | com.netease.protobuf.WireType.VARINT);

		private var prestige$field:uint;

		private var hasField$0:uint = 0;

		public function clearPrestige():void {
			hasField$0 &= 0xfffffffe;
			prestige$field = new uint();
		}

		public function get hasPrestige():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set prestige(value:uint):void {
			hasField$0 |= 0x1;
			prestige$field = value;
		}

		public function get prestige():uint {
			return prestige$field;
		}

		/**
		 *  @private
		 */
		public static const TOKEN_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.token_ts", "tokenTs", (68 << 3) | com.netease.protobuf.WireType.VARINT);

		public var tokenTs:uint;

		/**
		 *  @private
		 */
		public static const DAILY_REFRESH_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.daily_refresh_ts", "dailyRefreshTs", (69 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dailyRefreshTs:uint;

		/**
		 *  @private
		 */
		public static const DAILY_REWARD_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.daily_reward_times", "dailyRewardTimes", (70 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dailyRewardTimes:uint;

		/**
		 *  @private
		 */
		public static const DAILY_FREE_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.daily_free_times", "dailyFreeTimes", (71 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dailyFreeTimes:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.registerPlatform);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.registerTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.inviteUid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastLoginPlatform);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastLoginTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loginTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loginDays);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastActiveTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastOffTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.forbidTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.forbidReason);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.inviteCount);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.todayInviteCount);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 14);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.tutorialStage);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 15);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 16);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.fig);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 17);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kingdom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 18);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 19);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 20);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.acccharge);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 21);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.viplevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 22);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 23);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 24);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 25);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 26);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.iron);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 27);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ticket);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 28);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.silk);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 29);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.order);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 30);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.bag);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 31);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.preward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 32);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loyal);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 33);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.sacrifice);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 34);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.market);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 35);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.bmarketcd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 36);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.banquet);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 37);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.eshopintimacy);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 38);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.eshopcd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 39);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 40);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.arefresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 41);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.harmmer);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 42);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.shadow);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 43);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.upResTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 44);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rests);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 45);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 46);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 47);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mk1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 48);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mk2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 49);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewardb);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 50);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp3);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 51);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.npcPass);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 52);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.flamenCoinsCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 53);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.flamemWoodCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 54);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.flamemFoodCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 55);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.flamemIronCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 56);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.firstRecharge);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 57);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.autoBuildFlag);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 58);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.integralTimeCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 59);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.missionTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 60);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.missionId);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 61);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.vipReward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 62);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ladder);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 63);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ladderTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 64);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.jobRewardTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 65);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.department);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 66);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.official);
			if (hasPrestige) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 67);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, prestige$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 68);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.tokenTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 69);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dailyRefreshTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 70);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dailyRewardTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 71);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dailyFreeTimes);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var register_platform$count:uint = 0;
			var register_time$count:uint = 0;
			var invite_uid$count:uint = 0;
			var last_login_platform$count:uint = 0;
			var last_login_time$count:uint = 0;
			var login_times$count:uint = 0;
			var login_days$count:uint = 0;
			var last_active_time$count:uint = 0;
			var last_off_time$count:uint = 0;
			var forbid_ts$count:uint = 0;
			var forbid_reason$count:uint = 0;
			var invite_count$count:uint = 0;
			var today_invite_count$count:uint = 0;
			var tutorial_stage$count:uint = 0;
			var name$count:uint = 0;
			var fig$count:uint = 0;
			var kingdom$count:uint = 0;
			var exp$count:uint = 0;
			var level$count:uint = 0;
			var acccharge$count:uint = 0;
			var viplevel$count:uint = 0;
			var cash$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var ticket$count:uint = 0;
			var silk$count:uint = 0;
			var order$count:uint = 0;
			var bag$count:uint = 0;
			var preward$count:uint = 0;
			var loyal$count:uint = 0;
			var sacrifice$count:uint = 0;
			var market$count:uint = 0;
			var bmarketcd$count:uint = 0;
			var banquet$count:uint = 0;
			var eshopintimacy$count:uint = 0;
			var eshopcd$count:uint = 0;
			var refresh$count:uint = 0;
			var arefresh$count:uint = 0;
			var harmmer$count:uint = 0;
			var shadow$count:uint = 0;
			var up_res_time$count:uint = 0;
			var rests$count:uint = 0;
			var mp1$count:uint = 0;
			var mp2$count:uint = 0;
			var mk1$count:uint = 0;
			var mk2$count:uint = 0;
			var rewardb$count:uint = 0;
			var mp3$count:uint = 0;
			var npc_pass$count:uint = 0;
			var flamen_coins_cnt$count:uint = 0;
			var flamem_wood_cnt$count:uint = 0;
			var flamem_food_cnt$count:uint = 0;
			var flamem_iron_cnt$count:uint = 0;
			var first_recharge$count:uint = 0;
			var auto_build_flag$count:uint = 0;
			var integral_time_cnt$count:uint = 0;
			var mission_time$count:uint = 0;
			var mission_id$count:uint = 0;
			var vip_reward$count:uint = 0;
			var ladder$count:uint = 0;
			var ladder_ts$count:uint = 0;
			var job_reward_ts$count:uint = 0;
			var department$count:uint = 0;
			var official$count:uint = 0;
			var prestige$count:uint = 0;
			var token_ts$count:uint = 0;
			var daily_refresh_ts$count:uint = 0;
			var daily_reward_times$count:uint = 0;
			var daily_free_times$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (register_platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.registerPlatform cannot be set twice.');
					}
					++register_platform$count;
					this.registerPlatform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (register_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.registerTime cannot be set twice.');
					}
					++register_time$count;
					this.registerTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (invite_uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.inviteUid cannot be set twice.');
					}
					++invite_uid$count;
					this.inviteUid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (last_login_platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastLoginPlatform cannot be set twice.');
					}
					++last_login_platform$count;
					this.lastLoginPlatform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (last_login_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastLoginTime cannot be set twice.');
					}
					++last_login_time$count;
					this.lastLoginTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (login_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.loginTimes cannot be set twice.');
					}
					++login_times$count;
					this.loginTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (login_days$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.loginDays cannot be set twice.');
					}
					++login_days$count;
					this.loginDays = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (last_active_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastActiveTime cannot be set twice.');
					}
					++last_active_time$count;
					this.lastActiveTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (last_off_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastOffTime cannot be set twice.');
					}
					++last_off_time$count;
					this.lastOffTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (forbid_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.forbidTs cannot be set twice.');
					}
					++forbid_ts$count;
					this.forbidTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (forbid_reason$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.forbidReason cannot be set twice.');
					}
					++forbid_reason$count;
					this.forbidReason = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 12:
					if (invite_count$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.inviteCount cannot be set twice.');
					}
					++invite_count$count;
					this.inviteCount = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (today_invite_count$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.todayInviteCount cannot be set twice.');
					}
					++today_invite_count$count;
					this.todayInviteCount = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 14:
					if (tutorial_stage$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.tutorialStage cannot be set twice.');
					}
					++tutorial_stage$count;
					this.tutorialStage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 15:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 16:
					if (fig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.fig cannot be set twice.');
					}
					++fig$count;
					this.fig = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 17:
					if (kingdom$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.kingdom cannot be set twice.');
					}
					++kingdom$count;
					this.kingdom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 18:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 19:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 20:
					if (acccharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.acccharge cannot be set twice.');
					}
					++acccharge$count;
					this.acccharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 21:
					if (viplevel$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.viplevel cannot be set twice.');
					}
					++viplevel$count;
					this.viplevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 22:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 23:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 24:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 25:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 26:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 27:
					if (ticket$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.ticket cannot be set twice.');
					}
					++ticket$count;
					this.ticket = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 28:
					if (silk$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.silk cannot be set twice.');
					}
					++silk$count;
					this.silk = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 29:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 30:
					if (bag$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.bag cannot be set twice.');
					}
					++bag$count;
					this.bag = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 31:
					if (preward$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.preward cannot be set twice.');
					}
					++preward$count;
					this.preward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 32:
					if (loyal$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.loyal cannot be set twice.');
					}
					++loyal$count;
					this.loyal = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 33:
					if (sacrifice$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.sacrifice cannot be set twice.');
					}
					++sacrifice$count;
					this.sacrifice = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 34:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.market cannot be set twice.');
					}
					++market$count;
					this.market = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 35:
					if (bmarketcd$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.bmarketcd cannot be set twice.');
					}
					++bmarketcd$count;
					this.bmarketcd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 36:
					if (banquet$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.banquet cannot be set twice.');
					}
					++banquet$count;
					this.banquet = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 37:
					if (eshopintimacy$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.eshopintimacy cannot be set twice.');
					}
					++eshopintimacy$count;
					this.eshopintimacy = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 38:
					if (eshopcd$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.eshopcd cannot be set twice.');
					}
					++eshopcd$count;
					this.eshopcd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 39:
					if (refresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.refresh cannot be set twice.');
					}
					++refresh$count;
					this.refresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 40:
					if (arefresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.arefresh cannot be set twice.');
					}
					++arefresh$count;
					this.arefresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 41:
					if (harmmer$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.harmmer cannot be set twice.');
					}
					++harmmer$count;
					this.harmmer = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 42:
					if (shadow$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.shadow cannot be set twice.');
					}
					++shadow$count;
					this.shadow = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 43:
					if (up_res_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.upResTime cannot be set twice.');
					}
					++up_res_time$count;
					this.upResTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 44:
					if (rests$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.rests cannot be set twice.');
					}
					++rests$count;
					this.rests = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 45:
					if (mp1$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.mp1 cannot be set twice.');
					}
					++mp1$count;
					this.mp1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 46:
					if (mp2$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.mp2 cannot be set twice.');
					}
					++mp2$count;
					this.mp2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 47:
					if (mk1$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.mk1 cannot be set twice.');
					}
					++mk1$count;
					this.mk1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 48:
					if (mk2$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.mk2 cannot be set twice.');
					}
					++mk2$count;
					this.mk2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 49:
					if (rewardb$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.rewardb cannot be set twice.');
					}
					++rewardb$count;
					this.rewardb = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 50:
					if (mp3$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.mp3 cannot be set twice.');
					}
					++mp3$count;
					this.mp3 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 51:
					if (npc_pass$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.npcPass cannot be set twice.');
					}
					++npc_pass$count;
					this.npcPass = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 52:
					if (flamen_coins_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.flamenCoinsCnt cannot be set twice.');
					}
					++flamen_coins_cnt$count;
					this.flamenCoinsCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 53:
					if (flamem_wood_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.flamemWoodCnt cannot be set twice.');
					}
					++flamem_wood_cnt$count;
					this.flamemWoodCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 54:
					if (flamem_food_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.flamemFoodCnt cannot be set twice.');
					}
					++flamem_food_cnt$count;
					this.flamemFoodCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 55:
					if (flamem_iron_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.flamemIronCnt cannot be set twice.');
					}
					++flamem_iron_cnt$count;
					this.flamemIronCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 56:
					if (first_recharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.firstRecharge cannot be set twice.');
					}
					++first_recharge$count;
					this.firstRecharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 57:
					if (auto_build_flag$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.autoBuildFlag cannot be set twice.');
					}
					++auto_build_flag$count;
					this.autoBuildFlag = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 58:
					if (integral_time_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.integralTimeCnt cannot be set twice.');
					}
					++integral_time_cnt$count;
					this.integralTimeCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 59:
					if (mission_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.missionTime cannot be set twice.');
					}
					++mission_time$count;
					this.missionTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 60:
					if (mission_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.missionId cannot be set twice.');
					}
					++mission_id$count;
					this.missionId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 61:
					if (vip_reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.vipReward cannot be set twice.');
					}
					++vip_reward$count;
					this.vipReward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 62:
					if (ladder$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.ladder cannot be set twice.');
					}
					++ladder$count;
					this.ladder = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 63:
					if (ladder_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.ladderTs cannot be set twice.');
					}
					++ladder_ts$count;
					this.ladderTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 64:
					if (job_reward_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.jobRewardTs cannot be set twice.');
					}
					++job_reward_ts$count;
					this.jobRewardTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 65:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 66:
					if (official$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.official cannot be set twice.');
					}
					++official$count;
					this.official = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 67:
					if (prestige$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.prestige cannot be set twice.');
					}
					++prestige$count;
					this.prestige = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 68:
					if (token_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.tokenTs cannot be set twice.');
					}
					++token_ts$count;
					this.tokenTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 69:
					if (daily_refresh_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.dailyRefreshTs cannot be set twice.');
					}
					++daily_refresh_ts$count;
					this.dailyRefreshTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 70:
					if (daily_reward_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.dailyRewardTimes cannot be set twice.');
					}
					++daily_reward_times$count;
					this.dailyRewardTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 71:
					if (daily_free_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.dailyFreeTimes cannot be set twice.');
					}
					++daily_free_times$count;
					this.dailyFreeTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
