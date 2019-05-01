package ProtoEquip {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class SoldEquipResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const SOLDEQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoEquip.SoldEquipResp.soldequip", "soldequip", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentCPP; });

		public var soldequip:DataCommon.EquipmentCPP;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoEquip.SoldEquipResp.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.soldequip);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var soldequip$count:uint = 0;
			var coin$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (soldequip$count != 0) {
						throw new flash.errors.IOError('Bad data format: SoldEquipResp.soldequip cannot be set twice.');
					}
					++soldequip$count;
					this.soldequip = new DataCommon.EquipmentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.soldequip);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: SoldEquipResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
