package ProtoCrossBusiness {
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
	public dynamic final class BusinessRefreshReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ISCASH:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoCrossBusiness.BusinessRefreshReq.iscash", "iscash", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var iscash:Boolean;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.iscash);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var iscash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (iscash$count != 0) {
						throw new flash.errors.IOError('Bad data format: BusinessRefreshReq.iscash cannot be set twice.');
					}
					++iscash$count;
					this.iscash = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
