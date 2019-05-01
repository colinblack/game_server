package ProtoOfficial {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class DepartmentRecord extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PARAMS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentRecord.params", "params", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var params:uint;

		/**
		 *  @private
		 */
		public static const OPERATE:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.DepartmentRecord.operate", "operate", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var operate:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const TARGET:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.DepartmentRecord.target", "target", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var target:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const OPERATE_JOB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentRecord.operate_job", "operateJob", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var operateJob:uint;

		/**
		 *  @private
		 */
		public static const TARGET_JOB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentRecord.target_job", "targetJob", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var targetJob:uint;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentRecord.ts", "ts", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const OP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentRecord.op", "op", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var op:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.params);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.operate);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.target);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.operateJob);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.targetJob);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.op);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var params$count:uint = 0;
			var operate$count:uint = 0;
			var target$count:uint = 0;
			var operate_job$count:uint = 0;
			var target_job$count:uint = 0;
			var ts$count:uint = 0;
			var op$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (params$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.params cannot be set twice.');
					}
					++params$count;
					this.params = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (operate$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.operate cannot be set twice.');
					}
					++operate$count;
					this.operate = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 3:
					if (target$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.target cannot be set twice.');
					}
					++target$count;
					this.target = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 4:
					if (operate_job$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.operateJob cannot be set twice.');
					}
					++operate_job$count;
					this.operateJob = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (target_job$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.targetJob cannot be set twice.');
					}
					++target_job$count;
					this.targetJob = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (op$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentRecord.op cannot be set twice.');
					}
					++op$count;
					this.op = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
