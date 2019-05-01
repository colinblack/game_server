package ProtoFriend {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoFriend.FriendGiftCPP;
	import ProtoFriend.FriendCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class SendGiftResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const YOURFRIEND:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoFriend.SendGiftResp.yourfriend", "yourfriend", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoFriend.FriendCPP; });

		public var yourfriend:ProtoFriend.FriendCPP;

		/**
		 *  @private
		 */
		public static const FRIENDGIFT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoFriend.SendGiftResp.friendgift", "friendgift", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoFriend.FriendGiftCPP; });

		public var friendgift:ProtoFriend.FriendGiftCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.yourfriend);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.friendgift);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var yourfriend$count:uint = 0;
			var friendgift$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (yourfriend$count != 0) {
						throw new flash.errors.IOError('Bad data format: SendGiftResp.yourfriend cannot be set twice.');
					}
					++yourfriend$count;
					this.yourfriend = new ProtoFriend.FriendCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.yourfriend);
					break;
				case 2:
					if (friendgift$count != 0) {
						throw new flash.errors.IOError('Bad data format: SendGiftResp.friendgift cannot be set twice.');
					}
					++friendgift$count;
					this.friendgift = new ProtoFriend.FriendGiftCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.friendgift);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
