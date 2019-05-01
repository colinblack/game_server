package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoActivity.SellComponentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenSellComponentWindowResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const SELLINFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.OpenSellComponentWindowResp.sellinfo", "sellinfo", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.SellComponentCPP; });

		public var sellinfo:ProtoActivity.SellComponentCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.sellinfo);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var sellinfo$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (sellinfo$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenSellComponentWindowResp.sellinfo cannot be set twice.');
					}
					++sellinfo$count;
					this.sellinfo = new ProtoActivity.SellComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.sellinfo);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
