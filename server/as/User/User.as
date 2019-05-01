package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoYellowVip.YellowVipCPP;
	import User.Weapon;
	import ProtoAchievement.AchievementAllCPP;
	import DataCommon.EquipShopCPP;
	import User.Hero;
	import ProtoBattleField.ReplyRewardInfo;
	import ProtoOfficial.PublishToken;
	import User.Base;
	import ProtoBattleField.Field;
	import ProtoCumulation.CumulationCPP;
	import User.TimeLimtPropItem;
	import ProtoDailyMission.DailyMissionAllCPP;
	import ProtoFogGate.FogGateCPPAll;
	import User.Building;
	import ProtoMission.MissionAllCPP;
	import User.NPCPass;
	import User.EliteNPCInfoAll;
	import User.Activity;
	import DataCommon.EquipmentCPP;
	import User.Science;
	import ProtoMarket.MarketCPP;
	import ProtoComponent.ComponentAllCPP;
	import User.MineItem;
	import ProtoComponent.ProduceComponentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class User extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.base", "base", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Base; });

		public var base:User.Base;

		/**
		 *  @private
		 */
		public static const BUILDING:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.building", "building", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Building; });

		public var building:User.Building;

		/**
		 *  @private
		 */
		public static const HEROES:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.heroes", "heroes", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Hero; });

		public var heroes:User.Hero;

		/**
		 *  @private
		 */
		public static const EQUIP:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.User.equip", "equip", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentCPP; });

		[ArrayElementType("DataCommon.EquipmentCPP")]
		public var equip:Array = [];

		/**
		 *  @private
		 */
		public static const EQUIPSHOP:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.User.equipshop", "equipshop", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipShopCPP; });

		[ArrayElementType("DataCommon.EquipShopCPP")]
		public var equipshop:Array = [];

		/**
		 *  @private
		 */
		public static const FIELD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.field", "field", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Field; });

		public var field:ProtoBattleField.Field;

		/**
		 *  @private
		 */
		public static const MISSION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.mission", "mission", (7 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMission.MissionAllCPP; });

		public var mission:ProtoMission.MissionAllCPP;

		/**
		 *  @private
		 */
		public static const SCIENCE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.science", "science", (8 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Science; });

		public var science:User.Science;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.User.ts", "ts", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const YELLOWVIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.yellowvip", "yellowvip", (10 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoYellowVip.YellowVipCPP; });

		public var yellowvip:ProtoYellowVip.YellowVipCPP;

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.market", "market", (11 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMarket.MarketCPP; });

		private var market$field:ProtoMarket.MarketCPP;

		public function clearMarket():void {
			market$field = null;
		}

		public function get hasMarket():Boolean {
			return market$field != null;
		}

		public function set market(value:ProtoMarket.MarketCPP):void {
			market$field = value;
		}

		public function get market():ProtoMarket.MarketCPP {
			return market$field;
		}

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.reward", "reward", (12 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.ReplyRewardInfo; });

		public var reward:ProtoBattleField.ReplyRewardInfo;

		/**
		 *  @private
		 */
		public static const WEAPON:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.weapon", "weapon", (13 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Weapon; });

		public var weapon:User.Weapon;

		/**
		 *  @private
		 */
		public static const NPCPASS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.npcpass", "npcpass", (14 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.NPCPass; });

		public var npcpass:User.NPCPass;

		/**
		 *  @private
		 */
		public static const CUMULATION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.cumulation", "cumulation", (15 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoCumulation.CumulationCPP; });

		public var cumulation:ProtoCumulation.CumulationCPP;

		/**
		 *  @private
		 */
		public static const ACTIVITY:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.activity", "activity", (16 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Activity; });

		public var activity:User.Activity;

		/**
		 *  @private
		 */
		public static const TOKEN:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.User.token", "token", (17 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.PublishToken; });

		[ArrayElementType("ProtoOfficial.PublishToken")]
		public var token:Array = [];

		/**
		 *  @private
		 */
		public static const FOGGATES:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.foggates", "foggates", (18 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoFogGate.FogGateCPPAll; });

		public var foggates:ProtoFogGate.FogGateCPPAll;

		/**
		 *  @private
		 */
		public static const MINE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.mine", "mine", (19 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.MineItem; });

		public var mine:User.MineItem;

		/**
		 *  @private
		 */
		public static const DAILYMISSIONS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.dailymissions", "dailymissions", (20 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoDailyMission.DailyMissionAllCPP; });

		public var dailymissions:ProtoDailyMission.DailyMissionAllCPP;

		/**
		 *  @private
		 */
		public static const TIME_LIMIT_PROPS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.User.time_limit_props", "timeLimitProps", (21 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.TimeLimtPropItem; });

		[ArrayElementType("User.TimeLimtPropItem")]
		public var timeLimitProps:Array = [];

		/**
		 *  @private
		 */
		public static const COMPONENTS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.components", "components", (22 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ComponentAllCPP; });

		public var components:ProtoComponent.ComponentAllCPP;

		/**
		 *  @private
		 */
		public static const PRODUCECOMPONENT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.producecomponent", "producecomponent", (23 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ProduceComponentCPP; });

		public var producecomponent:ProtoComponent.ProduceComponentCPP;

		/**
		 *  @private
		 */
		public static const ACHIEVEMENTS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.achievements", "achievements", (24 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoAchievement.AchievementAllCPP; });

		public var achievements:ProtoAchievement.AchievementAllCPP;

		/**
		 *  @private
		 */
		public static const ELITENPCS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.elitenpcs", "elitenpcs", (25 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.EliteNPCInfoAll; });

		public var elitenpcs:User.EliteNPCInfoAll;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.base);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.building);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.heroes);
			for (var equip$index:uint = 0; equip$index < this.equip.length; ++equip$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equip[equip$index]);
			}
			for (var equipshop$index:uint = 0; equipshop$index < this.equipshop.length; ++equipshop$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equipshop[equipshop$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.field);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mission);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.science);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.yellowvip);
			if (hasMarket) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, market$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 13);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.weapon);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 14);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.npcpass);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 15);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.cumulation);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 16);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.activity);
			for (var token$index:uint = 0; token$index < this.token.length; ++token$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 17);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.token[token$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 18);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.foggates);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 19);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mine);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 20);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.dailymissions);
			for (var timeLimitProps$index:uint = 0; timeLimitProps$index < this.timeLimitProps.length; ++timeLimitProps$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 21);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.timeLimitProps[timeLimitProps$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 22);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.components);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 23);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.producecomponent);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 24);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.achievements);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 25);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.elitenpcs);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var base$count:uint = 0;
			var building$count:uint = 0;
			var heroes$count:uint = 0;
			var field$count:uint = 0;
			var mission$count:uint = 0;
			var science$count:uint = 0;
			var ts$count:uint = 0;
			var yellowvip$count:uint = 0;
			var market$count:uint = 0;
			var reward$count:uint = 0;
			var weapon$count:uint = 0;
			var npcpass$count:uint = 0;
			var cumulation$count:uint = 0;
			var activity$count:uint = 0;
			var foggates$count:uint = 0;
			var mine$count:uint = 0;
			var dailymissions$count:uint = 0;
			var components$count:uint = 0;
			var producecomponent$count:uint = 0;
			var achievements$count:uint = 0;
			var elitenpcs$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.base cannot be set twice.');
					}
					++base$count;
					this.base = new User.Base();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 2:
					if (building$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.building cannot be set twice.');
					}
					++building$count;
					this.building = new User.Building();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.building);
					break;
				case 3:
					if (heroes$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.heroes cannot be set twice.');
					}
					++heroes$count;
					this.heroes = new User.Hero();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.heroes);
					break;
				case 4:
					this.equip.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataCommon.EquipmentCPP()));
					break;
				case 5:
					this.equipshop.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataCommon.EquipShopCPP()));
					break;
				case 6:
					if (field$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.field cannot be set twice.');
					}
					++field$count;
					this.field = new ProtoBattleField.Field();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.field);
					break;
				case 7:
					if (mission$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.mission cannot be set twice.');
					}
					++mission$count;
					this.mission = new ProtoMission.MissionAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.mission);
					break;
				case 8:
					if (science$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.science cannot be set twice.');
					}
					++science$count;
					this.science = new User.Science();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.science);
					break;
				case 9:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (yellowvip$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.yellowvip cannot be set twice.');
					}
					++yellowvip$count;
					this.yellowvip = new ProtoYellowVip.YellowVipCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.yellowvip);
					break;
				case 11:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.market cannot be set twice.');
					}
					++market$count;
					this.market = new ProtoMarket.MarketCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.market);
					break;
				case 12:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoBattleField.ReplyRewardInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 13:
					if (weapon$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.weapon cannot be set twice.');
					}
					++weapon$count;
					this.weapon = new User.Weapon();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.weapon);
					break;
				case 14:
					if (npcpass$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.npcpass cannot be set twice.');
					}
					++npcpass$count;
					this.npcpass = new User.NPCPass();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.npcpass);
					break;
				case 15:
					if (cumulation$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.cumulation cannot be set twice.');
					}
					++cumulation$count;
					this.cumulation = new ProtoCumulation.CumulationCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.cumulation);
					break;
				case 16:
					if (activity$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.activity cannot be set twice.');
					}
					++activity$count;
					this.activity = new User.Activity();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activity);
					break;
				case 17:
					this.token.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.PublishToken()));
					break;
				case 18:
					if (foggates$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.foggates cannot be set twice.');
					}
					++foggates$count;
					this.foggates = new ProtoFogGate.FogGateCPPAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.foggates);
					break;
				case 19:
					if (mine$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.mine cannot be set twice.');
					}
					++mine$count;
					this.mine = new User.MineItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.mine);
					break;
				case 20:
					if (dailymissions$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.dailymissions cannot be set twice.');
					}
					++dailymissions$count;
					this.dailymissions = new ProtoDailyMission.DailyMissionAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.dailymissions);
					break;
				case 21:
					this.timeLimitProps.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new User.TimeLimtPropItem()));
					break;
				case 22:
					if (components$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.components cannot be set twice.');
					}
					++components$count;
					this.components = new ProtoComponent.ComponentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.components);
					break;
				case 23:
					if (producecomponent$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.producecomponent cannot be set twice.');
					}
					++producecomponent$count;
					this.producecomponent = new ProtoComponent.ProduceComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.producecomponent);
					break;
				case 24:
					if (achievements$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.achievements cannot be set twice.');
					}
					++achievements$count;
					this.achievements = new ProtoAchievement.AchievementAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.achievements);
					break;
				case 25:
					if (elitenpcs$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.elitenpcs cannot be set twice.');
					}
					++elitenpcs$count;
					this.elitenpcs = new User.EliteNPCInfoAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.elitenpcs);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
