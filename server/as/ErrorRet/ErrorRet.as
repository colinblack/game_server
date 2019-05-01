package ErrorRet {
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
	public dynamic final class ErrorRet extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ERROR_RET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ErrorRet.ErrorRet.error_ret", "errorRet", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var errorRet:uint;

		/**
		 *  @private
		 */
		public static const ERROR_MSG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("ErrorRet.ErrorRet.error_msg", "errorMsg", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var errorMsg:String;

		/**
		 *  @private
		 */
		public static const REQUEST_MSG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("ErrorRet.ErrorRet.request_msg", "requestMsg", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var requestMsg:String;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.errorRet);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.errorMsg);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.requestMsg);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var error_ret$count:uint = 0;
			var error_msg$count:uint = 0;
			var request_msg$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (error_ret$count != 0) {
						throw new flash.errors.IOError('Bad data format: ErrorRet.errorRet cannot be set twice.');
					}
					++error_ret$count;
					this.errorRet = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (error_msg$count != 0) {
						throw new flash.errors.IOError('Bad data format: ErrorRet.errorMsg cannot be set twice.');
					}
					++error_msg$count;
					this.errorMsg = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 3:
					if (request_msg$count != 0) {
						throw new flash.errors.IOError('Bad data format: ErrorRet.requestMsg cannot be set twice.');
					}
					++request_msg$count;
					this.requestMsg = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
