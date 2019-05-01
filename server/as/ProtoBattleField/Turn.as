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
	public dynamic final class Turn extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const A_SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.a_shape", "aShape", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var aShape:uint;

		/**
		 *  @private
		 */
		public static const D_SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.d_shape", "dShape", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var dShape:uint;

		/**
		 *  @private
		 */
		public static const ATT_SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.att_shape", "attShape", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attShape:uint;

		/**
		 *  @private
		 */
		public static const DEF_SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.def_shape", "defShape", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var defShape:uint;

		/**
		 *  @private
		 */
		public static const A_SKILL:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.a_skill", "aSkill", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var aSkill:Array = [];

		/**
		 *  @private
		 */
		public static const D_SKILL:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.d_skill", "dSkill", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var dSkill:Array = [];

		/**
		 *  @private
		 */
		public static const A_ATTACK:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.a_attack", "aAttack", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var aAttack:Array = [];

		/**
		 *  @private
		 */
		public static const D_ATTACK:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.d_attack", "dAttack", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var dAttack:Array = [];

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.ts", "ts", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const NEXTTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.nextts", "nextts", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var nextts:uint;

		/**
		 *  @private
		 */
		public static const A_EXPLODE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.a_explode", "aExplode", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		private var a_explode$field:uint;

		private var hasField$0:uint = 0;

		public function clearAExplode():void {
			hasField$0 &= 0xfffffffe;
			a_explode$field = new uint();
		}

		public function get hasAExplode():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set aExplode(value:uint):void {
			hasField$0 |= 0x1;
			a_explode$field = value;
		}

		public function get aExplode():uint {
			return a_explode$field;
		}

		/**
		 *  @private
		 */
		public static const D_EXPLODE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.Turn.d_explode", "dExplode", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		private var d_explode$field:uint;

		public function clearDExplode():void {
			hasField$0 &= 0xfffffffd;
			d_explode$field = new uint();
		}

		public function get hasDExplode():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set dExplode(value:uint):void {
			hasField$0 |= 0x2;
			d_explode$field = value;
		}

		public function get dExplode():uint {
			return d_explode$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.aShape);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dShape);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.attShape);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.defShape);
			for (var aSkill$index:uint = 0; aSkill$index < this.aSkill.length; ++aSkill$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.aSkill[aSkill$index]);
			}
			for (var dSkill$index:uint = 0; dSkill$index < this.dSkill.length; ++dSkill$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dSkill[dSkill$index]);
			}
			for (var aAttack$index:uint = 0; aAttack$index < this.aAttack.length; ++aAttack$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.aAttack[aAttack$index]);
			}
			for (var dAttack$index:uint = 0; dAttack$index < this.dAttack.length; ++dAttack$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.dAttack[dAttack$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.nextts);
			if (hasAExplode) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, a_explode$field);
			}
			if (hasDExplode) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, d_explode$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var a_shape$count:uint = 0;
			var d_shape$count:uint = 0;
			var att_shape$count:uint = 0;
			var def_shape$count:uint = 0;
			var ts$count:uint = 0;
			var nextts$count:uint = 0;
			var a_explode$count:uint = 0;
			var d_explode$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (a_shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.aShape cannot be set twice.');
					}
					++a_shape$count;
					this.aShape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (d_shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.dShape cannot be set twice.');
					}
					++d_shape$count;
					this.dShape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (att_shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.attShape cannot be set twice.');
					}
					++att_shape$count;
					this.attShape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (def_shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.defShape cannot be set twice.');
					}
					++def_shape$count;
					this.defShape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.aSkill);
						break;
					}
					this.aSkill.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 6:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.dSkill);
						break;
					}
					this.dSkill.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 7:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.aAttack);
						break;
					}
					this.aAttack.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 8:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.dAttack);
						break;
					}
					this.dAttack.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 9:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (nextts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.nextts cannot be set twice.');
					}
					++nextts$count;
					this.nextts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (a_explode$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.aExplode cannot be set twice.');
					}
					++a_explode$count;
					this.aExplode = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (d_explode$count != 0) {
						throw new flash.errors.IOError('Bad data format: Turn.dExplode cannot be set twice.');
					}
					++d_explode$count;
					this.dExplode = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
