package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleTurnInfo
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleTurnInfo";
		public var package_root:*;
		public  var message:*;
		public var info:ProtoBattleTurn;
		public var attr:ProtoBattleAttr;
		public var cards:BattleCardsCPP;
		public var addPoint:int;
		public function ProtoBattleTurnInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
			attr = undefined;
			cards = undefined;
			addPoint = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.info!= undefined)
			{
				serializeObj.info = this.info.serialize();
			}
			if(this.attr!= undefined)
			{
				serializeObj.attr = this.attr.serialize();
			}
			if(this.cards!= undefined)
			{
				serializeObj.cards = this.cards.serialize();
			}
			if(this.addPoint!= undefined)
			{
				serializeObj.addPoint = this.addPoint;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleTurnInfo
		{
			info = undefined;
			attr = undefined;
			cards = undefined;
			addPoint = undefined;
			if(msgObj.hasOwnProperty("info"))
			{
				this.info = new ProtoBattleTurn(package_root).unserialize(msgObj.info);
			}
			if(msgObj.hasOwnProperty("attr"))
			{
				this.attr = new ProtoBattleAttr(package_root).unserialize(msgObj.attr);
			}
			if(msgObj.hasOwnProperty("cards"))
			{
				this.cards = new BattleCardsCPP(package_root).unserialize(msgObj.cards);
			}
			if(msgObj.hasOwnProperty("addPoint"))
			{
				this.addPoint = msgObj.addPoint;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleTurnInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}