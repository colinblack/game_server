package Bot {
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
	public dynamic final class ChatInfo extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Bot.ChatInfo.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("Bot.ChatInfo.name", "name", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const KINGDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Bot.ChatInfo.kingdom", "kingdom", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kingdom:uint;

		/**
		 *  @private
		 */
		public static const VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Bot.ChatInfo.vip", "vip", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var vip:uint;

		/**
		 *  @private
		 */
		public static const LVL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Bot.ChatInfo.lvl", "lvl", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lvl:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kingdom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.vip);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lvl);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var name$count:uint = 0;
			var kingdom$count:uint = 0;
			var vip$count:uint = 0;
			var lvl$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ChatInfo.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: ChatInfo.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 3:
					if (kingdom$count != 0) {
						throw new flash.errors.IOError('Bad data format: ChatInfo.kingdom cannot be set twice.');
					}
					++kingdom$count;
					this.kingdom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: ChatInfo.vip cannot be set twice.');
					}
					++vip$count;
					this.vip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (lvl$count != 0) {
						throw new flash.errors.IOError('Bad data format: ChatInfo.lvl cannot be set twice.');
					}
					++lvl$count;
					this.lvl = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
