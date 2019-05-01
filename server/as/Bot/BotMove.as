package Bot {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import Bot.ChatInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BotMove extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const INFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("Bot.BotMove.info", "info", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return Bot.ChatInfo; });

		public var info:Bot.ChatInfo;

		/**
		 *  @private
		 */
		public static const ID:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("Bot.BotMove.id", "id", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var id:Array = [];

		/**
		 *  @private
		 */
		public static const CIDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("Bot.BotMove.cids", "cids", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var cids:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.info);
			for (var id$index:uint = 0; id$index < this.id.length; ++id$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id[id$index]);
			}
			for (var cids$index:uint = 0; cids$index < this.cids.length; ++cids$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cids[cids$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var info$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (info$count != 0) {
						throw new flash.errors.IOError('Bad data format: BotMove.info cannot be set twice.');
					}
					++info$count;
					this.info = new Bot.ChatInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.info);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.id);
						break;
					}
					this.id.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.cids);
						break;
					}
					this.cids.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
