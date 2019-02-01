package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClubInfo
	{
		public static const PROTO:String = "ProtoMartialClub.MartialClubInfo";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var grade:int;
		public var level:int;
		public var nextTs:int;
		public var protectTs:int;
		public var martialName:String;
		public var incomeStartTs:int;
		public var coins:int;
		public var props:Vector.<MartialClubProp>;
		public function MartialClubInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			grade = undefined;
			level = undefined;
			nextTs = undefined;
			protectTs = undefined;
			martialName = undefined;
			incomeStartTs = undefined;
			coins = undefined;
			props = new Vector.<MartialClubProp>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.grade = this.grade;
			serializeObj.level = this.level;
			serializeObj.nextTs = this.nextTs;
			serializeObj.protectTs = this.protectTs;
			serializeObj.martialName = this.martialName;
			serializeObj.incomeStartTs = this.incomeStartTs;
			serializeObj.coins = this.coins;
			serializeObj.props = [];
			for(var i:int = 0;i < this.props.length;i++)
			{
				serializeObj.props.push(this.props[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClubInfo
		{
			uid = undefined;
			grade = undefined;
			level = undefined;
			nextTs = undefined;
			protectTs = undefined;
			martialName = undefined;
			incomeStartTs = undefined;
			coins = undefined;
			props = new Vector.<MartialClubProp>();
			this.uid = msgObj.uid;
			this.grade = msgObj.grade;
			this.level = msgObj.level;
			this.nextTs = msgObj.nextTs;
			this.protectTs = msgObj.protectTs;
			this.martialName = msgObj.martialName;
			this.incomeStartTs = msgObj.incomeStartTs;
			this.coins = msgObj.coins;
			for(var i:int = 0;i < msgObj.props.length;i++)
			{
				this.props.push(new MartialClubProp(package_root).unserialize(msgObj.props[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClubInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}