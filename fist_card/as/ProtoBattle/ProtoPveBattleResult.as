package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoPveBattleResult
	{
		public static const PROTO:String = "ProtoBattle.ProtoPveBattleResult";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var dropCards:CardsAllChangeCPP;
		public function ProtoPveBattleResult(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
			dropCards = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			if(this.dropCards!= undefined)
			{
				serializeObj.dropCards = this.dropCards.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoPveBattleResult
		{
			commons = undefined;
			dropCards = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			if(msgObj.hasOwnProperty("dropCards"))
			{
				this.dropCards = new CardsAllChangeCPP(package_root).unserialize(msgObj.dropCards);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoPveBattleResult
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}