package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleInfo
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleInfo";
		public var package_root:*;
		public  var message:*;
		public var actionType:int;
		public var aim:int;
		public var att:ProtoBattleTurnInfo;
		public var def:ProtoBattleTurnInfo;
		public function ProtoBattleInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			actionType = undefined;
			aim = undefined;
			att = undefined;
			def = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.actionType = this.actionType;
			serializeObj.aim = this.aim;
			if(this.att!= undefined)
			{
				serializeObj.att = this.att.serialize();
			}
			if(this.def!= undefined)
			{
				serializeObj.def = this.def.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleInfo
		{
			actionType = undefined;
			aim = undefined;
			att = undefined;
			def = undefined;
			this.actionType = msgObj.actionType;
			this.aim = msgObj.aim;
			if(msgObj.hasOwnProperty("att"))
			{
				this.att = new ProtoBattleTurnInfo(package_root).unserialize(msgObj.att);
			}
			if(msgObj.hasOwnProperty("def"))
			{
				this.def = new ProtoBattleTurnInfo(package_root).unserialize(msgObj.def);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}