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
	public dynamic final class FriendCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const FRIEND_UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendCPP.friend_uid", "friendUid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var friendUid:uint;

		/**
		 *  @private
		 */
		public static const SEND_GIFT_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendCPP.send_gift_ts", "sendGiftTs", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var sendGiftTs:uint;

		/**
		 *  @private
		 */
		public static const ISONLINE:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoFriend.FriendCPP.isonline", "isonline", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isonline:Boolean;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoFriend.FriendCPP.name", "name", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const KINDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendCPP.kindom", "kindom", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kindom:uint;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoFriend.FriendCPP.level", "level", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.friendUid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.sendGiftTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isonline);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kindom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var friend_uid$count:uint = 0;
			var send_gift_ts$count:uint = 0;
			var isonline$count:uint = 0;
			var name$count:uint = 0;
			var kindom$count:uint = 0;
			var level$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (friend_uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.friendUid cannot be set twice.');
					}
					++friend_uid$count;
					this.friendUid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (send_gift_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.sendGiftTs cannot be set twice.');
					}
					++send_gift_ts$count;
					this.sendGiftTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (isonline$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.isonline cannot be set twice.');
					}
					++isonline$count;
					this.isonline = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 4:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 5:
					if (kindom$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.kindom cannot be set twice.');
					}
					++kindom$count;
					this.kindom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: FriendCPP.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
