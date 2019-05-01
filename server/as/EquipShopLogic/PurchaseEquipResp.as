package EquipShopLogic {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipShopCPP;
	import DataCommon.EquipmentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PurchaseEquipResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("EquipShopLogic.PurchaseEquipResp.equip", "equip", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentCPP; });

		private var equip$field:DataCommon.EquipmentCPP;

		public function clearEquip():void {
			equip$field = null;
		}

		public function get hasEquip():Boolean {
			return equip$field != null;
		}

		public function set equip(value:DataCommon.EquipmentCPP):void {
			equip$field = value;
		}

		public function get equip():DataCommon.EquipmentCPP {
			return equip$field;
		}

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.PurchaseEquipResp.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const EQUIPPOOL:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("EquipShopLogic.PurchaseEquipResp.equippool", "equippool", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipShopCPP; });

		[ArrayElementType("DataCommon.EquipShopCPP")]
		public var equippool:Array = [];

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.PurchaseEquipResp.order", "order", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var order:uint;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.PurchaseEquipResp.iron", "iron", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var iron:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasEquip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, equip$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			for (var equippool$index:uint = 0; equippool$index < this.equippool.length; ++equippool$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equippool[equippool$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.order);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.iron);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equip$count:uint = 0;
			var coin$count:uint = 0;
			var order$count:uint = 0;
			var iron$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equip$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipResp.equip cannot be set twice.');
					}
					++equip$count;
					this.equip = new DataCommon.EquipmentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equip);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					this.equippool.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataCommon.EquipShopCPP()));
					break;
				case 4:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipResp.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipResp.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
