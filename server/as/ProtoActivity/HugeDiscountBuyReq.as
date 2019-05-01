package ProtoActivity {
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
	public dynamic final class HugeDiscountBuyReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PAGE_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.HugeDiscountBuyReq.page_id", "pageId", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var pageId:uint;

		/**
		 *  @private
		 */
		public static const ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.HugeDiscountBuyReq.id", "id", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var id:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.pageId);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var page_id$count:uint = 0;
			var id$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (page_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyReq.pageId cannot be set twice.');
					}
					++page_id$count;
					this.pageId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (id$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyReq.id cannot be set twice.');
					}
					++id$count;
					this.id = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
