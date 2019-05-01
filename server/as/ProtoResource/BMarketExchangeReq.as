package ProtoResource {
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
	public dynamic final class BMarketExchangeReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const USEDTYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.BMarketExchangeReq.usedtype", "usedtype", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var usedtype:uint;

		/**
		 *  @private
		 */
		public static const GAINTYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoResource.BMarketExchangeReq.gaintype", "gaintype", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gaintype:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.usedtype);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gaintype);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var usedtype$count:uint = 0;
			var gaintype$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (usedtype$count != 0) {
						throw new flash.errors.IOError('Bad data format: BMarketExchangeReq.usedtype cannot be set twice.');
					}
					++usedtype$count;
					this.usedtype = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (gaintype$count != 0) {
						throw new flash.errors.IOError('Bad data format: BMarketExchangeReq.gaintype cannot be set twice.');
					}
					++gaintype$count;
					this.gaintype = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
