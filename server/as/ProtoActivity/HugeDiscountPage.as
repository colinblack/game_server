package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoActivity.HugeDiscountItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class HugeDiscountPage extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PAGE_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.HugeDiscountPage.page_id", "pageId", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var pageId:uint;

		/**
		 *  @private
		 */
		public static const GOODS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoActivity.HugeDiscountPage.goods", "goods", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.HugeDiscountItem; });

		[ArrayElementType("ProtoActivity.HugeDiscountItem")]
		public var goods:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.pageId);
			for (var goods$index:uint = 0; goods$index < this.goods.length; ++goods$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.goods[goods$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var page_id$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (page_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountPage.pageId cannot be set twice.');
					}
					++page_id$count;
					this.pageId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.goods.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoActivity.HugeDiscountItem()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
