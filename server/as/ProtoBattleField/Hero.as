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
	public dynamic final class Hero extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.id", "id", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var id:uint;

		/**
		 *  @private
		 */
		public static const PROPERTY:RepeatedFieldDescriptor_TYPE_INT32 = new RepeatedFieldDescriptor_TYPE_INT32("ProtoBattleField.Hero.property", "property", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("int")]
		public var property:Array = [];

		/**
		 *  @private
		 */
		public static const HP:RepeatedFieldDescriptor_TYPE_INT32 = new RepeatedFieldDescriptor_TYPE_INT32("ProtoBattleField.Hero.hp", "hp", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("int")]
		public var hp:Array = [];

		/**
		 *  @private
		 */
		public static const SHAPE:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.shape", "shape", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var shape:Array = [];

		/**
		 *  @private
		 */
		public static const SKILL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.skill", "skill", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var skill$field:uint;

		private var hasField$0:uint = 0;

		public function clearSkill():void {
			hasField$0 &= 0xfffffffe;
			skill$field = new uint();
		}

		public function get hasSkill():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set skill(value:uint):void {
			hasField$0 |= 0x1;
			skill$field = value;
		}

		public function get skill():uint {
			return skill$field;
		}

		/**
		 *  @private
		 */
		public static const EXTRAID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.extraid", "extraid", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var extraid:uint;

		/**
		 *  @private
		 */
		public static const CITY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.city", "city", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var city:uint;

		/**
		 *  @private
		 */
		public static const GATE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.gate", "gate", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gate:uint;

		/**
		 *  @private
		 */
		public static const OUID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.ouid", "ouid", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		private var ouid$field:uint;

		public function clearOuid():void {
			hasField$0 &= 0xfffffffd;
			ouid$field = new uint();
		}

		public function get hasOuid():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set ouid(value:uint):void {
			hasField$0 |= 0x2;
			ouid$field = value;
		}

		public function get ouid():uint {
			return ouid$field;
		}

		/**
		 *  @private
		 */
		public static const OID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Hero.oid", "oid", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		private var oid$field:uint;

		public function clearOid():void {
			hasField$0 &= 0xfffffffb;
			oid$field = new uint();
		}

		public function get hasOid():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set oid(value:uint):void {
			hasField$0 |= 0x4;
			oid$field = value;
		}

		public function get oid():uint {
			return oid$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id);
			for (var property$index:uint = 0; property$index < this.property.length; ++property$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.property[property$index]);
			}
			for (var hp$index:uint = 0; hp$index < this.hp.length; ++hp$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.hp[hp$index]);
			}
			for (var shape$index:uint = 0; shape$index < this.shape.length; ++shape$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.shape[shape$index]);
			}
			if (hasSkill) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, skill$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.extraid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.city);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gate);
			if (hasOuid) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, ouid$field);
			}
			if (hasOid) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, oid$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var id$count:uint = 0;
			var skill$count:uint = 0;
			var extraid$count:uint = 0;
			var city$count:uint = 0;
			var gate$count:uint = 0;
			var ouid$count:uint = 0;
			var oid$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (id$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.id cannot be set twice.');
					}
					++id$count;
					this.id = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_INT32, this.property);
						break;
					}
					this.property.push(com.netease.protobuf.ReadUtils.read_TYPE_INT32(input));
					break;
				case 3:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_INT32, this.hp);
						break;
					}
					this.hp.push(com.netease.protobuf.ReadUtils.read_TYPE_INT32(input));
					break;
				case 4:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.shape);
						break;
					}
					this.shape.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 5:
					if (skill$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.skill cannot be set twice.');
					}
					++skill$count;
					this.skill = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (extraid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.extraid cannot be set twice.');
					}
					++extraid$count;
					this.extraid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (city$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.city cannot be set twice.');
					}
					++city$count;
					this.city = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (gate$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.gate cannot be set twice.');
					}
					++gate$count;
					this.gate = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (ouid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.ouid cannot be set twice.');
					}
					++ouid$count;
					this.ouid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (oid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Hero.oid cannot be set twice.');
					}
					++oid$count;
					this.oid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
