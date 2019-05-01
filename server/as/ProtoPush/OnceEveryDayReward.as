package ProtoPush {
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
	public dynamic final class OnceEveryDayReward extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const INTEGRAL_TIME_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.integral_time_cnt", "integralTimeCnt", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var integralTimeCnt:uint;

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.market", "market", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var market:uint;

		/**
		 *  @private
		 */
		public static const SACRIFICE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.sacrifice", "sacrifice", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var sacrifice:uint;

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.order", "order", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var order:uint;

		/**
		 *  @private
		 */
		public static const REFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.refresh", "refresh", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refresh:uint;

		/**
		 *  @private
		 */
		public static const LADDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.ladder", "ladder", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ladder:uint;

		/**
		 *  @private
		 */
		public static const FREEREFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.freerefresh", "freerefresh", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var freerefresh:uint;

		/**
		 *  @private
		 */
		public static const REWARD_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPush.OnceEveryDayReward.reward_times", "rewardTimes", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardTimes:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.integralTimeCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.market);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.sacrifice);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.order);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ladder);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.freerefresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewardTimes);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var integral_time_cnt$count:uint = 0;
			var market$count:uint = 0;
			var sacrifice$count:uint = 0;
			var order$count:uint = 0;
			var refresh$count:uint = 0;
			var ladder$count:uint = 0;
			var freerefresh$count:uint = 0;
			var reward_times$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (integral_time_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.integralTimeCnt cannot be set twice.');
					}
					++integral_time_cnt$count;
					this.integralTimeCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.market cannot be set twice.');
					}
					++market$count;
					this.market = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (sacrifice$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.sacrifice cannot be set twice.');
					}
					++sacrifice$count;
					this.sacrifice = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (refresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.refresh cannot be set twice.');
					}
					++refresh$count;
					this.refresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (ladder$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.ladder cannot be set twice.');
					}
					++ladder$count;
					this.ladder = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (freerefresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.freerefresh cannot be set twice.');
					}
					++freerefresh$count;
					this.freerefresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (reward_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: OnceEveryDayReward.rewardTimes cannot be set twice.');
					}
					++reward_times$count;
					this.rewardTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
