package ProtoFriend {
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
	public dynamic final class FriendGiftCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PRESTIGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.prestige", "prestige", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var prestige:uint;

		/**
		 *  @private
		 */
		public static const GRADES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.grades", "grades", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var grades:uint;

		/**
		 *  @private
		 */
		public static const RECEIVE_GIFT_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.receive_gift_times", "receiveGiftTimes", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var receiveGiftTimes:uint;

		/**
		 *  @private
		 */
		public static const RECEIVE_GIFT_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.receive_gift_ts", "receiveGiftTs", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var receiveGiftTs:uint;

		/**
		 *  @private
		 */
		public static const SEND_GIFT_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.send_gift_times", "sendGiftTimes", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var sendGiftTimes:uint;

		/**
		 *  @private
		 */
		public static const SEND_GIFT_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendGiftCPP.send_gift_ts", "sendGiftTs", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var sendGiftTs:uint;

		/**
		 *  @private
		 */
		public static const LOG_DATA:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoFriend.FriendGiftCPP.log_data", "logData", (7 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var logData:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.prestige);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.grades);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.receiveGiftTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.receiveGiftTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.sendGiftTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.sendGiftTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.logData);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var prestige$count:uint = 0;
			var grades$count:uint = 0;
			var receive_gift_times$count:uint = 0;
			var receive_gift_ts$count:uint = 0;
			var send_gift_times$count:uint = 0;
			var send_gift_ts$count:uint = 0;
			var log_data$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (prestige$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.prestige cannot be set twice.');
					}
					++prestige$count;
					this.prestige = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (grades$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.grades cannot be set twice.');
					}
					++grades$count;
					this.grades = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (receive_gift_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.receiveGiftTimes cannot be set twice.');
					}
					++receive_gift_times$count;
					this.receiveGiftTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (receive_gift_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.receiveGiftTs cannot be set twice.');
					}
					++receive_gift_ts$count;
					this.receiveGiftTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (send_gift_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.sendGiftTimes cannot be set twice.');
					}
					++send_gift_times$count;
					this.sendGiftTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (send_gift_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.sendGiftTs cannot be set twice.');
					}
					++send_gift_ts$count;
					this.sendGiftTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (log_data$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendGiftCPP.logData cannot be set twice.');
					}
					++log_data$count;
					this.logData = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
