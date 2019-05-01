package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentAllCPP;
	import ProtoActivity.HugeDiscountItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class HugeDiscountBuyResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PAGE_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.HugeDiscountBuyResp.page_id", "pageId", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var pageId:uint;

		/**
		 *  @private
		 */
		public static const ITEM_INFO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.HugeDiscountBuyResp.item_info", "itemInfo", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.HugeDiscountItem; });

		public var itemInfo:ProtoActivity.HugeDiscountItem;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.HugeDiscountBuyResp.cash", "cash", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const EQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.HugeDiscountBuyResp.equip", "equip", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		public var equip:DataCommon.EquipmentAllCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.pageId);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.itemInfo);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equip);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var page_id$count:uint = 0;
			var item_info$count:uint = 0;
			var cash$count:uint = 0;
			var equip$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (page_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyResp.pageId cannot be set twice.');
					}
					++page_id$count;
					this.pageId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (item_info$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyResp.itemInfo cannot be set twice.');
					}
					++item_info$count;
					this.itemInfo = new ProtoActivity.HugeDiscountItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.itemInfo);
					break;
				case 3:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (equip$count != 0) {
						throw new flash.errors.IOError('Bad data format: HugeDiscountBuyResp.equip cannot be set twice.');
					}
					++equip$count;
					this.equip = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equip);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
