package Common {
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
	public dynamic final class NoticePay extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.NoticePay.cash", "cash", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const VIP_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.NoticePay.vip_level", "vipLevel", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var vipLevel:uint;

		/**
		 *  @private
		 */
		public static const ACC_RECHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.NoticePay.acc_recharge", "accRecharge", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var accRecharge:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.vipLevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.accRecharge);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var cash$count:uint = 0;
			var vip_level$count:uint = 0;
			var acc_recharge$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: NoticePay.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (vip_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: NoticePay.vipLevel cannot be set twice.');
					}
					++vip_level$count;
					this.vipLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (acc_recharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: NoticePay.accRecharge cannot be set twice.');
					}
					++acc_recharge$count;
					this.accRecharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
