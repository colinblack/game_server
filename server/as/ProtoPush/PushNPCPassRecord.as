package ProtoPush {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoPass.NPCPassRecord;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PushNPCPassRecord extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ITEM:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoPush.PushNPCPassRecord.item", "item", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoPass.NPCPassRecord; });

		public var item:ProtoPass.NPCPassRecord;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.item);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var item$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (item$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushNPCPassRecord.item cannot be set twice.');
					}
					++item$count;
					this.item = new ProtoPass.NPCPassRecord();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.item);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
