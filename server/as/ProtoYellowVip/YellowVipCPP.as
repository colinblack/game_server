package ProtoYellowVip {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class YellowVipCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const NEWERSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.newerstatus", "newerstatus", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var newerstatus:uint;

		/**
		 *  @private
		 */
		public static const DAILYSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.dailystatus", "dailystatus", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dailystatus:uint;

		/**
		 *  @private
		 */
		public static const YEARSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.yearstatus", "yearstatus", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var yearstatus:uint;

		/**
		 *  @private
		 */
		public static const LEVELSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.levelstatus", "levelstatus", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var levelstatus:uint;

		/**
		 *  @private
		 */
		public static const DAILY_REWARD_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.daily_reward_time", "dailyRewardTime", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dailyRewardTime:uint;

		/**
		 *  @private
		 */
		public static const YEAR_REWARD_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.year_reward_time", "yearRewardTime", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var yearRewardTime:uint;

		/**
		 *  @private
		 */
		public static const QQZONE_DAILYSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.qqzone_dailystatus", "qqzoneDailystatus", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var qqzoneDailystatus:uint;

		/**
		 *  @private
		 */
		public static const QQZONE_DAILY_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.qqzone_daily_time", "qqzoneDailyTime", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var qqzoneDailyTime:uint;

		/**
		 *  @private
		 */
		public static const QQZONE_LEVELSTATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoYellowVip.YellowVipCPP.qqzone_levelstatus", "qqzoneLevelstatus", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var qqzoneLevelstatus:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.newerstatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dailystatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.yearstatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.levelstatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dailyRewardTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.yearRewardTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.qqzoneDailystatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.qqzoneDailyTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.qqzoneLevelstatus);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var newerstatus$count:uint = 0;
			var dailystatus$count:uint = 0;
			var yearstatus$count:uint = 0;
			var levelstatus$count:uint = 0;
			var daily_reward_time$count:uint = 0;
			var year_reward_time$count:uint = 0;
			var qqzone_dailystatus$count:uint = 0;
			var qqzone_daily_time$count:uint = 0;
			var qqzone_levelstatus$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (newerstatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.newerstatus cannot be set twice.');
					}
					++newerstatus$count;
					this.newerstatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (dailystatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.dailystatus cannot be set twice.');
					}
					++dailystatus$count;
					this.dailystatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (yearstatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.yearstatus cannot be set twice.');
					}
					++yearstatus$count;
					this.yearstatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (levelstatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.levelstatus cannot be set twice.');
					}
					++levelstatus$count;
					this.levelstatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (daily_reward_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.dailyRewardTime cannot be set twice.');
					}
					++daily_reward_time$count;
					this.dailyRewardTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (year_reward_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.yearRewardTime cannot be set twice.');
					}
					++year_reward_time$count;
					this.yearRewardTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (qqzone_dailystatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.qqzoneDailystatus cannot be set twice.');
					}
					++qqzone_dailystatus$count;
					this.qqzoneDailystatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (qqzone_daily_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.qqzoneDailyTime cannot be set twice.');
					}
					++qqzone_daily_time$count;
					this.qqzoneDailyTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (qqzone_levelstatus$count != 0) {
						throw new flash.errors.IOError('Bad data format: YellowVipCPP.qqzoneLevelstatus cannot be set twice.');
					}
					++qqzone_levelstatus$count;
					this.qqzoneLevelstatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
