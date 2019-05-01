package ProtoOfficial {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOfficial.DepartmentRecord;
	import ProtoOfficial.eDepartment;
	import flash.utils.ByteArray;
	import ProtoOfficial.DepartmentMember;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class AppointDeputyResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.AppointDeputyResp.department", "department", (1 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var department:int;

		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.AppointDeputyResp.uid", "uid", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const ORIGIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.AppointDeputyResp.origin", "origin", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var origin:uint;

		/**
		 *  @private
		 */
		public static const TARGET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.AppointDeputyResp.target", "target", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var target:uint;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.AppointDeputyResp.name", "name", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const MEMBERS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOfficial.AppointDeputyResp.members", "members", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentMember; });

		[ArrayElementType("ProtoOfficial.DepartmentMember")]
		public var members:Array = [];

		/**
		 *  @private
		 */
		public static const RECORDS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOfficial.AppointDeputyResp.records", "records", (7 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentRecord; });

		[ArrayElementType("ProtoOfficial.DepartmentRecord")]
		public var records:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.department);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.origin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.target);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			for (var members$index:uint = 0; members$index < this.members.length; ++members$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.members[members$index]);
			}
			for (var records$index:uint = 0; records$index < this.records.length; ++records$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.records[records$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var department$count:uint = 0;
			var uid$count:uint = 0;
			var origin$count:uint = 0;
			var target$count:uint = 0;
			var name$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: AppointDeputyResp.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 2:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: AppointDeputyResp.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (origin$count != 0) {
						throw new flash.errors.IOError('Bad data format: AppointDeputyResp.origin cannot be set twice.');
					}
					++origin$count;
					this.origin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (target$count != 0) {
						throw new flash.errors.IOError('Bad data format: AppointDeputyResp.target cannot be set twice.');
					}
					++target$count;
					this.target = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: AppointDeputyResp.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 6:
					this.members.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.DepartmentMember()));
					break;
				case 7:
					this.records.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.DepartmentRecord()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
