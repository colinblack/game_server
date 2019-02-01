package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleTurn
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleTurn";
		public var package_root:*;
		public  var message:*;
		public var dam:int;
		public var blood:int;
		public var hurtBack:int;
		public var attCast:int;
		public var crit:Boolean;
		public var invalid:Boolean;
		public var hurtTrans:Boolean;
		public var bomb:Boolean;
		public function ProtoBattleTurn(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			dam = undefined;
			blood = undefined;
			hurtBack = undefined;
			attCast = undefined;
			crit = undefined;
			invalid = undefined;
			hurtTrans = undefined;
			bomb = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.dam!= undefined)
			{
				serializeObj.dam = this.dam;
			}
			if(this.blood!= undefined)
			{
				serializeObj.blood = this.blood;
			}
			if(this.hurtBack!= undefined)
			{
				serializeObj.hurtBack = this.hurtBack;
			}
			if(this.attCast!= undefined)
			{
				serializeObj.attCast = this.attCast;
			}
			if(this.crit!= undefined)
			{
				serializeObj.crit = this.crit;
			}
			if(this.invalid!= undefined)
			{
				serializeObj.invalid = this.invalid;
			}
			if(this.hurtTrans!= undefined)
			{
				serializeObj.hurtTrans = this.hurtTrans;
			}
			if(this.bomb!= undefined)
			{
				serializeObj.bomb = this.bomb;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleTurn
		{
			dam = undefined;
			blood = undefined;
			hurtBack = undefined;
			attCast = undefined;
			crit = undefined;
			invalid = undefined;
			hurtTrans = undefined;
			bomb = undefined;
			if(msgObj.hasOwnProperty("dam"))
			{
				this.dam = msgObj.dam;
			}
			if(msgObj.hasOwnProperty("blood"))
			{
				this.blood = msgObj.blood;
			}
			if(msgObj.hasOwnProperty("hurtBack"))
			{
				this.hurtBack = msgObj.hurtBack;
			}
			if(msgObj.hasOwnProperty("attCast"))
			{
				this.attCast = msgObj.attCast;
			}
			if(msgObj.hasOwnProperty("crit"))
			{
				this.crit = msgObj.crit;
			}
			if(msgObj.hasOwnProperty("invalid"))
			{
				this.invalid = msgObj.invalid;
			}
			if(msgObj.hasOwnProperty("hurtTrans"))
			{
				this.hurtTrans = msgObj.hurtTrans;
			}
			if(msgObj.hasOwnProperty("bomb"))
			{
				this.bomb = msgObj.bomb;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleTurn
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}