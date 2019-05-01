package User {
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
	public dynamic final class CostCashReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.CostCashReq.cash", "cash", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const OP_CODE:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("User.CostCashReq.op_code", "opCode", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var opCode:String;

		/**
		 *  @private
		 */
		public static const OPERATION:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.CostCashReq.operation", "operation", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var operation:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.opCode);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.operation);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var cash$count:uint = 0;
			var op_code$count:uint = 0;
			var operation$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: CostCashReq.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (op_code$count != 0) {
						throw new flash.errors.IOError('Bad data format: CostCashReq.opCode cannot be set twice.');
					}
					++op_code$count;
					this.opCode = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 3:
					if (operation$count != 0) {
						throw new flash.errors.IOError('Bad data format: CostCashReq.operation cannot be set twice.');
					}
					++operation$count;
					this.operation = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
