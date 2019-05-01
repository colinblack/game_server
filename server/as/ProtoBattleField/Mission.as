package ProtoBattleField {
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
	public dynamic final class Mission extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const M1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Mission.m1", "m1", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var m1:uint;

		/**
		 *  @private
		 */
		public static const M2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Mission.m2", "m2", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var m2:uint;

		/**
		 *  @private
		 */
		public static const M1STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Mission.m1status", "m1status", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var m1status:uint;

		/**
		 *  @private
		 */
		public static const M2STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Mission.m2status", "m2status", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var m2status:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.m1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.m2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.m1status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.m2status);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var m1$count:uint = 0;
			var m2$count:uint = 0;
			var m1status$count:uint = 0;
			var m2status$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (m1$count != 0) {
						throw new flash.errors.IOError('Bad data format: Mission.m1 cannot be set twice.');
					}
					++m1$count;
					this.m1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (m2$count != 0) {
						throw new flash.errors.IOError('Bad data format: Mission.m2 cannot be set twice.');
					}
					++m2$count;
					this.m2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (m1status$count != 0) {
						throw new flash.errors.IOError('Bad data format: Mission.m1status cannot be set twice.');
					}
					++m1status$count;
					this.m1status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (m2status$count != 0) {
						throw new flash.errors.IOError('Bad data format: Mission.m2status cannot be set twice.');
					}
					++m2status$count;
					this.m2status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
