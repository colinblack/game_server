package Admin {
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
	public dynamic final class ReplyForbidTS extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const FORBID_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Admin.ReplyForbidTS.forbid_ts", "forbidTs", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var forbidTs:uint;

		/**
		 *  @private
		 */
		public static const REASON:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("Admin.ReplyForbidTS.reason", "reason", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var reason:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.forbidTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.reason);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var forbid_ts$count:uint = 0;
			var reason$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (forbid_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyForbidTS.forbidTs cannot be set twice.');
					}
					++forbid_ts$count;
					this.forbidTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (reason$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyForbidTS.reason cannot be set twice.');
					}
					++reason$count;
					this.reason = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
