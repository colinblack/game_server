package ProtoFriend {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.RewardItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReceiveGiftPushReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const RECV_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.ReceiveGiftPushReq.recv_times", "recvTimes", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var recvTimes:uint;

		/**
		 *  @private
		 */
		public static const RECV_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.ReceiveGiftPushReq.recv_ts", "recvTs", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var recvTs:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoFriend.ReceiveGiftPushReq.coin", "coin", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var coin:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		public static const PRESTIGE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoFriend.ReceiveGiftPushReq.prestige", "prestige", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var prestige:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.recvTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.recvTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.prestige);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var recv_times$count:uint = 0;
			var recv_ts$count:uint = 0;
			var coin$count:uint = 0;
			var prestige$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (recv_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveGiftPushReq.recvTimes cannot be set twice.');
					}
					++recv_times$count;
					this.recvTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (recv_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveGiftPushReq.recvTs cannot be set twice.');
					}
					++recv_ts$count;
					this.recvTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveGiftPushReq.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.coin);
					break;
				case 4:
					if (prestige$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveGiftPushReq.prestige cannot be set twice.');
					}
					++prestige$count;
					this.prestige = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.prestige);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
