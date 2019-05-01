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
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PrivilegeRecord extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const OPERATE:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.PrivilegeRecord.operate", "operate", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var operate:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const TARGET:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.PrivilegeRecord.target", "target", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var target:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.PrivilegeRecord.department", "department", (3 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var department:int;

		/**
		 *  @private
		 */
		public static const OFFICIAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.PrivilegeRecord.official", "official", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var official:uint;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.PrivilegeRecord.ts", "ts", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.PrivilegeRecord.type", "type", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type:uint;

		/**
		 *  @private
		 */
		public static const PARAMS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.PrivilegeRecord.params", "params", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var params:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.operate);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.target);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.department);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.official);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.params);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var operate$count:uint = 0;
			var target$count:uint = 0;
			var department$count:uint = 0;
			var official$count:uint = 0;
			var ts$count:uint = 0;
			var type$count:uint = 0;
			var params$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (operate$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.operate cannot be set twice.');
					}
					++operate$count;
					this.operate = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 2:
					if (target$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.target cannot be set twice.');
					}
					++target$count;
					this.target = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 3:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 4:
					if (official$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.official cannot be set twice.');
					}
					++official$count;
					this.official = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (params$count != 0) {
						throw new flash.errors.IOError('Bad data format: PrivilegeRecord.params cannot be set twice.');
					}
					++params$count;
					this.params = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
