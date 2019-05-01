package ProtoAchievement {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentAllCPP;
	import DataCommon.CommonBaseRewardCPP;
	import ProtoAchievement.AchievementCPP;
	import ProtoHero.HeroBaseInfoCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetAchievementRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIPS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAchievement.GetAchievementRewardResp.equips", "equips", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		private var equips$field:DataCommon.EquipmentAllCPP;

		public function clearEquips():void {
			equips$field = null;
		}

		public function get hasEquips():Boolean {
			return equips$field != null;
		}

		public function set equips(value:DataCommon.EquipmentAllCPP):void {
			equips$field = value;
		}

		public function get equips():DataCommon.EquipmentAllCPP {
			return equips$field;
		}

		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAchievement.GetAchievementRewardResp.base", "base", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CommonBaseRewardCPP; });

		private var base$field:DataCommon.CommonBaseRewardCPP;

		public function clearBase():void {
			base$field = null;
		}

		public function get hasBase():Boolean {
			return base$field != null;
		}

		public function set base(value:DataCommon.CommonBaseRewardCPP):void {
			base$field = value;
		}

		public function get base():DataCommon.CommonBaseRewardCPP {
			return base$field;
		}

		/**
		 *  @private
		 */
		public static const HERO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAchievement.GetAchievementRewardResp.hero", "hero", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		private var hero$field:ProtoHero.HeroBaseInfoCPP;

		public function clearHero():void {
			hero$field = null;
		}

		public function get hasHero():Boolean {
			return hero$field != null;
		}

		public function set hero(value:ProtoHero.HeroBaseInfoCPP):void {
			hero$field = value;
		}

		public function get hero():ProtoHero.HeroBaseInfoCPP {
			return hero$field;
		}

		/**
		 *  @private
		 */
		public static const ACHIEVEMENT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAchievement.GetAchievementRewardResp.achievement", "achievement", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoAchievement.AchievementCPP; });

		public var achievement:ProtoAchievement.AchievementCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasEquips) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, equips$field);
			}
			if (hasBase) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, base$field);
			}
			if (hasHero) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, hero$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.achievement);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equips$count:uint = 0;
			var base$count:uint = 0;
			var hero$count:uint = 0;
			var achievement$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equips$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAchievementRewardResp.equips cannot be set twice.');
					}
					++equips$count;
					this.equips = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equips);
					break;
				case 2:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAchievementRewardResp.base cannot be set twice.');
					}
					++base$count;
					this.base = new DataCommon.CommonBaseRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 3:
					if (hero$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAchievementRewardResp.hero cannot be set twice.');
					}
					++hero$count;
					this.hero = new ProtoHero.HeroBaseInfoCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hero);
					break;
				case 4:
					if (achievement$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetAchievementRewardResp.achievement cannot be set twice.');
					}
					++achievement$count;
					this.achievement = new ProtoAchievement.AchievementCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.achievement);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
