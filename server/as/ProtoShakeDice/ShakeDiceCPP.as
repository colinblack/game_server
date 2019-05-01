package ProtoShakeDice {
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
	public dynamic final class ShakeDiceCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const VERSION:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.version", "version", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var version:uint;

		/**
		 *  @private
		 */
		public static const CURMAP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.curmap", "curmap", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var curmap:uint;

		/**
		 *  @private
		 */
		public static const MAP1_STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map1_status", "map1Status", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map1Status:uint;

		/**
		 *  @private
		 */
		public static const MAP2_STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map2_status", "map2Status", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map2Status:uint;

		/**
		 *  @private
		 */
		public static const MAP3_STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map3_status", "map3Status", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map3Status:uint;

		/**
		 *  @private
		 */
		public static const DICE_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.dice_times", "diceTimes", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var diceTimes:uint;

		/**
		 *  @private
		 */
		public static const RESET_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.reset_times", "resetTimes", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var resetTimes:uint;

		/**
		 *  @private
		 */
		public static const STEPS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.steps", "steps", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var steps:uint;

		/**
		 *  @private
		 */
		public static const OPERATE_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.operate_ts", "operateTs", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var operateTs:uint;

		/**
		 *  @private
		 */
		public static const EXTRA_REWARD_STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.extra_reward_status", "extraRewardStatus", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var extraRewardStatus:uint;

		/**
		 *  @private
		 */
		public static const MAP1_REWARDS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map1_rewards", "map1Rewards", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map1Rewards:uint;

		/**
		 *  @private
		 */
		public static const MAP2_REWARDS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map2_rewards", "map2Rewards", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map2Rewards:uint;

		/**
		 *  @private
		 */
		public static const MAP3_REWARDS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.map3_rewards", "map3Rewards", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		public var map3Rewards:uint;

		/**
		 *  @private
		 */
		public static const CURPOS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoShakeDice.ShakeDiceCPP.curpos", "curpos", (14 << 3) | com.netease.protobuf.WireType.VARINT);

		public var curpos:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.version);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.curmap);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map1Status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map2Status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map3Status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.diceTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.resetTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.steps);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.operateTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.extraRewardStatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map1Rewards);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map2Rewards);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.map3Rewards);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 14);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.curpos);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var version$count:uint = 0;
			var curmap$count:uint = 0;
			var map1_status$count:uint = 0;
			var map2_status$count:uint = 0;
			var map3_status$count:uint = 0;
			var dice_times$count:uint = 0;
			var reset_times$count:uint = 0;
			var steps$count:uint = 0;
			var operate_ts$count:uint = 0;
			var extra_reward_status$count:uint = 0;
			var map1_rewards$count:uint = 0;
			var map2_rewards$count:uint = 0;
			var map3_rewards$count:uint = 0;
			var curpos$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (version$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.version cannot be set twice.');
					}
					++version$count;
					this.version = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (curmap$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.curmap cannot be set twice.');
					}
					++curmap$count;
					this.curmap = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (map1_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map1Status cannot be set twice.');
					}
					++map1_status$count;
					this.map1Status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (map2_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map2Status cannot be set twice.');
					}
					++map2_status$count;
					this.map2Status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (map3_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map3Status cannot be set twice.');
					}
					++map3_status$count;
					this.map3Status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (dice_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.diceTimes cannot be set twice.');
					}
					++dice_times$count;
					this.diceTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (reset_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.resetTimes cannot be set twice.');
					}
					++reset_times$count;
					this.resetTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (steps$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.steps cannot be set twice.');
					}
					++steps$count;
					this.steps = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (operate_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.operateTs cannot be set twice.');
					}
					++operate_ts$count;
					this.operateTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (extra_reward_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.extraRewardStatus cannot be set twice.');
					}
					++extra_reward_status$count;
					this.extraRewardStatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (map1_rewards$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map1Rewards cannot be set twice.');
					}
					++map1_rewards$count;
					this.map1Rewards = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (map2_rewards$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map2Rewards cannot be set twice.');
					}
					++map2_rewards$count;
					this.map2Rewards = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (map3_rewards$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.map3Rewards cannot be set twice.');
					}
					++map3_rewards$count;
					this.map3Rewards = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 14:
					if (curpos$count != 0) {
						throw new flash.errors.IOError('Bad data format: ShakeDiceCPP.curpos cannot be set twice.');
					}
					++curpos$count;
					this.curpos = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
