package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoComputerCards
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoComputerCards";
		public var package_root:*;
		public  var message:*;
		public var cardid:int;
		public var battle:Vector.<ProtoBattleInfo>;
		public function ProtoComputerCards(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			cardid = undefined;
			battle = new Vector.<ProtoBattleInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cardid = this.cardid;
			serializeObj.battle = [];
			for(var i:int = 0;i < this.battle.length;i++)
			{
				serializeObj.battle.push(this.battle[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoComputerCards
		{
			cardid = undefined;
			battle = new Vector.<ProtoBattleInfo>();
			this.cardid = msgObj.cardid;
			for(var i:int = 0;i < msgObj.battle.length;i++)
			{
				this.battle.push(new ProtoBattleInfo(package_root).unserialize(msgObj.battle[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoComputerCards
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}