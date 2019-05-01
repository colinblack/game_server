package ProtoComponent {
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
	public dynamic final class ProduceComponentCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CURRENT_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ProduceComponentCPP.current_level", "currentLevel", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var currentLevel:uint;

		/**
		 *  @private
		 */
		public static const ISPAYCASH:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoComponent.ProduceComponentCPP.ispaycash", "ispaycash", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ispaycash:Boolean;

		/**
		 *  @private
		 */
		public static const TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ProduceComponentCPP.times", "times", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var times:uint;

		/**
		 *  @private
		 */
		public static const PAYCASH_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ProduceComponentCPP.paycash_ts", "paycashTs", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var paycashTs:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.currentLevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.ispaycash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.times);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.paycashTs);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var current_level$count:uint = 0;
			var ispaycash$count:uint = 0;
			var times$count:uint = 0;
			var paycash_ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (current_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProduceComponentCPP.currentLevel cannot be set twice.');
					}
					++current_level$count;
					this.currentLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (ispaycash$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProduceComponentCPP.ispaycash cannot be set twice.');
					}
					++ispaycash$count;
					this.ispaycash = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 3:
					if (times$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProduceComponentCPP.times cannot be set twice.');
					}
					++times$count;
					this.times = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (paycash_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProduceComponentCPP.paycashTs cannot be set twice.');
					}
					++paycash_ts$count;
					this.paycashTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
