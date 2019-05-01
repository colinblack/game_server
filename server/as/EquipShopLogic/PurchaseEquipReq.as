package EquipShopLogic {
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
	public dynamic final class PurchaseEquipReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.PurchaseEquipReq.pid", "pid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var pid:uint;

		/**
		 *  @private
		 */
		public static const EQID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("EquipShopLogic.PurchaseEquipReq.eqid", "eqid", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var eqid:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.pid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.eqid);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var pid$count:uint = 0;
			var eqid$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (pid$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipReq.pid cannot be set twice.');
					}
					++pid$count;
					this.pid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (eqid$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseEquipReq.eqid cannot be set twice.');
					}
					++eqid$count;
					this.eqid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
