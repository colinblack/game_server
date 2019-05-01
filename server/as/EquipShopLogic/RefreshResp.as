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
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class RefreshResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CDTIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.RefreshResp.cdtime", "cdtime", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cdtime:uint;

		/**
		 *  @private
		 */
		public static const EQUIPPOOL:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("EquipShopLogic.RefreshResp.equippool", "equippool", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipShopCPP; });

		[ArrayElementType("DataCommon.EquipShopCPP")]
		public var equippool:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cdtime);
			for (var equippool$index:uint = 0; equippool$index < this.equippool.length; ++equippool$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equippool[equippool$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var cdtime$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (cdtime$count != 0) {
						throw new flash.errors.IOError('Bad data format: RefreshResp.cdtime cannot be set twice.');
					}
					++cdtime$count;
					this.cdtime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.equippool.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataCommon.EquipShopCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
