package ProtoOfficial {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOfficial.eDepartment;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PushJobChangeMsg extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ORIGIN_DEPART:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.PushJobChangeMsg.origin_depart", "originDepart", (1 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var originDepart:int;

		/**
		 *  @private
		 */
		public static const ORIGIN_JOB:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoOfficial.PushJobChangeMsg.origin_job", "originJob", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var originJob:int;

		/**
		 *  @private
		 */
		public static const TARGET_DEPART:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.PushJobChangeMsg.target_depart", "targetDepart", (3 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var targetDepart:int;

		/**
		 *  @private
		 */
		public static const TARGET_JOB:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoOfficial.PushJobChangeMsg.target_job", "targetJob", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var targetJob:int;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.originDepart);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.originJob);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.targetDepart);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.targetJob);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var origin_depart$count:uint = 0;
			var origin_job$count:uint = 0;
			var target_depart$count:uint = 0;
			var target_job$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (origin_depart$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushJobChangeMsg.originDepart cannot be set twice.');
					}
					++origin_depart$count;
					this.originDepart = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 2:
					if (origin_job$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushJobChangeMsg.originJob cannot be set twice.');
					}
					++origin_job$count;
					this.originJob = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 3:
					if (target_depart$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushJobChangeMsg.targetDepart cannot be set twice.');
					}
					++target_depart$count;
					this.targetDepart = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 4:
					if (target_job$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushJobChangeMsg.targetJob cannot be set twice.');
					}
					++target_job$count;
					this.targetJob = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
