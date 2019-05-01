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
	import ProtoActivity.SmeltItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class SmeltRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ITEM:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.SmeltRewardResp.item", "item", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.SmeltItem; });

		public var item:ProtoActivity.SmeltItem;

		/**
		 *  @private
		 */
		public static const EQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.SmeltRewardResp.equip", "equip", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		public var equip:DataCommon.EquipmentAllCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.item);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equip);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var item$count:uint = 0;
			var equip$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (item$count != 0) {
						throw new flash.errors.IOError('Bad data format: SmeltRewardResp.item cannot be set twice.');
					}
					++item$count;
					this.item = new ProtoActivity.SmeltItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.item);
					break;
				case 2:
					if (equip$count != 0) {
						throw new flash.errors.IOError('Bad data format: SmeltRewardResp.equip cannot be set twice.');
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
